#include "Database.h"
#include <sstream>

namespace inventory
{
	const std::vector<std::string> Database::TABLE_COLS_REG { "id", "product_id", "type", "quantity", "price", "total", "datetime" };
	std::string Database::TABLE_COLS_REG_STR {};
	const std::vector<std::string> Database::TABLE_COLS_PROD { "id", "name", "price", "minQuantity", "description" };
	std::string Database::TABLE_COLS_PROD_STR {};

	Database& Database::GetInstance()
	{
		if (TABLE_COLS_REG_STR.empty() && !TABLE_COLS_REG.empty()) {
			size_t size = TABLE_COLS_REG.size();

			for (int i = 0; i < size; i++) {
				TABLE_COLS_REG_STR += (i == 0 ? "" : ", ") + TABLE_COLS_REG[i];
			}
		}

		if (TABLE_COLS_PROD_STR.empty() && !TABLE_COLS_PROD.empty()) {
			size_t size = TABLE_COLS_PROD.size();

			for (int i = 0; i < size; i++) {
				TABLE_COLS_PROD_STR += (i == 0 ? "" : ", ") + TABLE_COLS_PROD[i];
			}
		}

		static Database instance;
		return instance;
	}

	bool Database::connect(const DatabaseConnParams& params)
	{
		delete session;

		// trying to connect
		try {
			session = new mysqlx::Session(params.host, params.port, params.user, params.password);
		}
		catch (const mysqlx::Error& err) {
			error = err.what();
			return false;
		}
		catch (std::exception& ex) {
			error = ex.what();
			return false;
		}
		catch (...) {
			error = "UNKNOWN EXCEPTION";
			return false;
		}

		session->sql("USE " + params.schema).execute();
		return true;
	}

	const std::string& Database::getError()
	{
		return error;
	}

#pragma region Registries
	int Database::getRegistryCount()
	{
		const mysqlx::Value r = session->sql("SELECT COUNT(*) FROM registry")
			.execute()
			.fetchOne()[0];

		return r.get<int>();
	}

	void Database::getRegistryById(int registryId, Registry& reg)
	{
		std::stringstream query;

		query << "SELECT " << TABLE_COLS_REG_STR << " FROM registry WHERE id = ?";

		const mysqlx::Row row = session->sql(query.str())
			.bind(registryId)
			.execute()
			.fetchOne();

		if (!row.colCount()) {
			reg.id = NO_ID;
			return;
		}

		registryFromRow(row, reg);
	}

	void Database::getRegistries(std::vector<Registry>& regs)
	{
		std::stringstream query;

		query << "SELECT " << TABLE_COLS_REG_STR << " FROM registry ORDER BY datetime DESC";

		std::vector<mysqlx::Row> rows = session->sql(query.str())
			.execute()
			.fetchAll();

		registryFromRow(rows, regs);
	}

	void Database::getRegistries(std::vector<Registry>& regs, int limit, int startIndex)
	{
		std::stringstream query;
		
		query << "SELECT " << TABLE_COLS_REG_STR << " FROM registry ORDER BY datetime DESC LIMIT ? OFFSET ?";

		std::vector<mysqlx::Row> rows = session->sql(query.str())
			.bind(limit)
			.bind(startIndex)
			.execute()
			.fetchAll();

		registryFromRow(rows, regs);
	}

	void Database::getRegistriesByRange(std::vector<Registry>& regs, const std::string& dtstart, const std::string& dtend)
	{
		std::stringstream query;

		query << "SELECT " << TABLE_COLS_REG_STR << " FROM registry WHERE datetime BETWEEN ? AND ? ORDER BY datetime";

		std::vector<mysqlx::Row> rows = session->sql(query.str())
			.bind(dtstart)
			.bind(dtend)
			.execute()
			.fetchAll();

		registryFromRow(rows, regs);
	}

	void Database::addRegistry(Registry& reg)
	{
		std::stringstream query;

		query << "INSERT INTO registry (" << TABLE_COLS_REG_STR << ") VALUES (" << getPlaceHolderFromTable(TABLE_COLS_REG) << ")";

		mysqlx::SqlResult result = session->sql(query.str())
			.bind(reg.id)
			.bind(reg.productId)
			.bind(reg.type == RegistryType::In ? 1 : 0)
			.bind(reg.quantity)
			.bind(reg.price)
			.bind(reg.total)
			.bind(reg.datetime)
			.execute();
		reg.id = static_cast<int>(result.getAutoIncrementValue());
	}

	void Database::updateRegistry(const Registry& reg)
	{
		std::stringstream query;

		query
			<< "UPDATE registry SET "
			<< getPlaceHolderFromTable(TABLE_COLS_REG, true, true)
			<< " WHERE id = ?";

		session->sql(query.str())
			.bind(reg.productId)
			.bind(reg.type == RegistryType::In ? 1 : 0)
			.bind(reg.quantity)
			.bind(reg.price)
			.bind(reg.total)
			.bind(reg.datetime)
			.bind(reg.id)
			.execute();
	}

	void Database::deleteRegistry(int registryId)
	{
		session->sql("DELETE FROM registry WHERE id = ?")
			.bind(registryId)
			.execute();
	}

#pragma endregion Registries

#pragma region Products
	int Database::getProductCount()
	{
		mysqlx::Value r = session->sql("SELECT COUNT(*) FROM product").execute().fetchOne()[0];
		return r.get<int>();
	}

	void Database::getProductById(int productId, Product& prod)
	{
		std::stringstream query;

		query << "SELECT " << TABLE_COLS_PROD_STR << " FROM product WHERE id = ?";

		const mysqlx::Row row = session->sql(query.str())
			.bind(productId)
			.execute()
			.fetchOne();

		if (!row.colCount()) {
			prod.id = NO_ID;
			return;
		}

		productFromRow(row, prod);
	}

	void Database::getProducts(std::vector<Product>& products)
	{
		std::stringstream query;

		query << "SELECT " << TABLE_COLS_PROD_STR << " FROM product";

		std::vector<mysqlx::Row> rows = session->sql(query.str())
			.execute()
			.fetchAll();

		productFromRow(rows, products);
	}

	void Database::getProducts(std::vector<Product>& products, int limit, int startIndex)
	{
		std::stringstream query;

		query << "SELECT " << TABLE_COLS_PROD_STR << " FROM product LIMIT ? OFFSET ?";

		std::vector<mysqlx::Row> rows = session->sql(query.str())
			.bind(limit)
			.bind(startIndex)
			.execute()
			.fetchAll();

		productFromRow(rows, products);
	}

	void Database::addProduct(Product& prod)
	{
		std::stringstream query;

		query << "INSERT INTO product (" << TABLE_COLS_PROD_STR << ") VALUES (" << getPlaceHolderFromTable(TABLE_COLS_PROD);

		mysqlx::SqlResult result = session->sql(query.str())
			.bind(prod.name)
			.bind(prod.price)
			.bind(prod.minQuantity)
			.bind(prod.description)
			.execute();
		prod.id = static_cast<int>(result.getAutoIncrementValue());
	}

	void Database::updateProduct(const Product& prod)
	{
		std::stringstream query;

		query << "UPDATE PRODUCT SET " << getPlaceHolderFromTable(TABLE_COLS_PROD, true, true) << " WHERE id = ?";

		session->sql(query.str())
			.bind(prod.name)
			.bind(prod.price)
			.bind(prod.minQuantity)
			.bind(prod.description)
			.bind(prod.id)
			.execute();
	}

	void Database::deleteProduct(int productId)
	{
		session->sql("DELETE FROM product WHERE id = ?")
			.bind(productId)
			.execute();
	}

#pragma endregion Products

	Database::Database()
		: session(nullptr)
	{
	}

	Database::~Database()
	{
		if (session) session->close();
		delete session;
	}

	void Database::registryFromRow(const mysqlx::Row& row, Registry& reg)
	{
		reg.id = row[0].get<int>();
		reg.productId = row[1].get<int>();
		reg.type = row[2].get<int>() ? RegistryType::In : RegistryType::Out;
		reg.quantity = row[3].get<int>();
		reg.price = row[4].get<double>();
		reg.total = row[5].get<double>();
		reg.datetime = row[6].get<std::string>();
	}

	void Database::registryFromRow(const std::vector<mysqlx::Row>& rows, std::vector<Registry>& regs)
	{
		regs.clear();

		for (const auto& row : rows) {
			regs.emplace_back(
				row[0].get<int>(),
				row[1].get<int>(),
				row[2].get<int>() ? RegistryType::In : RegistryType::Out,
				row[3].get<int>(),
				row[4].get<double>(),
				row[5].get<double>(),
				row[6].get<std::string>()
			);
		}
	}

	void Database::productFromRow(const mysqlx::Row& row, Product& prod)
	{
		prod.id = row[0].get<int>();
		prod.name = row[1].get<std::string>();
		prod.price = row[2].get<double>();
		prod.minQuantity = row[3].get<int>();
		prod.description = row[4].get<std::string>();
	}
	void Database::productFromRow(const std::vector<mysqlx::Row>& rows, std::vector<Product>& prods)
	{
		prods.clear();

		for (const auto& row : rows) {
			prods.emplace_back(
				row[0].get<int>(),
				row[1].get<std::string>(),
				row[2].get<double>(),
				row[3].get<int>(),
				row[4].get<std::string>()
			);
		}
	}
	std::string Database::getPlaceHolderFromTable(const std::vector<std::string>& cols, bool keyValue, bool ignoreId)
	{
		std::string out;
		int index = 0;

		for (const auto& col : cols) {
			if (ignoreId && col == "id")
				continue;

			if (index == 0) {
				out += keyValue ? ("`" + col + "` = ?") : ("?");
			}
			else {
				out += keyValue ? (", `" + col + "` = ?") : ", ?";
			}
		}

		return out;
	}
}