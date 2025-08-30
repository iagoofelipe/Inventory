#include "Database.h"
#include "config.h"

#include <string>
#include <iostream>
#include <vector>

namespace server
{

	Database& Database::getInstance()
	{
		static Database instance; // Instantiated on first use.
		return instance;
	}

	bool Database::connect()
	{
		std::string
			host = getConfig("host"),
			user = getConfig("user"),
			schema = getConfig("database"),
			_port, password;

		delete session;

		// checking whether the configuration is valid
		if (host.empty() || user.empty() || schema.empty()) {
			error = "invalid configuration";
			session = nullptr;
			return false;
		}
	
		_port = getConfig("port");
		password = getConfig("password");
		int port = !_port.empty() ? std::stoi(_port) : 33060;

		// trying to connect
		try {
			session = new mysqlx::Session(host, port, user, password);
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

		session->sql("USE " + schema).execute();
		return true;
	}

	const std::string& Database::getError()
	{
		return error;
	}

	void Database::test()
	{
		mysqlx::SqlStatement stmt = session->sql("SELECT Name, Population FROM world.country WHERE Population > 100000000 ORDER BY Population DESC");
		mysqlx::SqlResult result = stmt.execute();

		std::cout << "[Database] Countries with population over 100 million (biggest first):" << std::endl;
		for (const auto& row : result.fetchAll()) {
			std::cout << "\tName: " << row[0] << ", Population: " << row[1] << std::endl;
		}
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
		const mysqlx::Row row = session->sql("SELECT id, product_id, type, quantity, price, total, datetime FROM registry WHERE id = ?")
			.bind(registryId)
			.execute()
			.fetchOne();

		if(!row.colCount()) {
			reg.id = NO_ID;
			return;
		}

		generateRegistryFromRow(row, reg);
	}

	void Database::getRegistries(std::vector<Registry>& regs)
	{
		regs.clear();

		std::vector<mysqlx::Row> rows = session->sql("SELECT id, product_id, type, quantity, price, total, datetime FROM product")
			.execute()
			.fetchAll();

		for (const auto& row : rows) {
			Registry r;
			generateRegistryFromRow(row, r);
			regs.push_back(r);
		}
	}

	void Database::getRegistries(std::vector<Registry>& regs, int limit, int startIndex)
	{
		regs.clear();

		std::vector<mysqlx::Row> rows = session->sql("SELECT id, product_id, type, quantity, price, total, datetime FROM product LIMIT ? OFFSET ?")
			.bind(limit)
			.bind(startIndex)
			.execute()
			.fetchAll();

		for (const auto& row : rows) {
			Registry r;
			generateRegistryFromRow(row, r);
			regs.push_back(r);
		}
	}

	void Database::addRegistry(Registry& reg)
	{
		mysqlx::SqlResult result = session->sql("INSERT INTO registry (product_id, type, quantity, price, total, datetime) VALUES (?, ?, ?, ?, ?, ?)")
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
		session->sql("UPDATE registry SET product_id = ?, type = ?, quantity = ?, price = ?, total = ?, datetime = ? WHERE id = ?")
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
		const mysqlx::Row row = session->sql("SELECT id, name, price, minQuantity, description FROM product WHERE id = ?")
			.bind(productId)
			.execute()
			.fetchOne();

		if (!row.colCount()) {
			prod.id = NO_ID;
			return;
		}

		generateProductFromRow(row, prod);
	}

	void Database::getProducts(std::vector<Product>& regs)
	{
		regs.clear();

		std::vector<mysqlx::Row> rows = session->sql("SELECT id, name, price, minQuantity, description FROM product")
			.execute()
			.fetchAll();

		for (const auto& row : rows) {
			Product p;
			generateProductFromRow(row, p);
			regs.push_back(p);
		}
	}

	void Database::getProducts(std::vector<Product>& regs, int limit, int startIndex)
	{
		regs.clear();

		std::vector<mysqlx::Row> rows = session->sql("SELECT id, name, price, minQuantity, description FROM product LIMIT ? OFFSET ?")
			.bind(limit)
			.bind(startIndex)
			.execute()
			.fetchAll();

		for (const auto& row : rows) {
			Product p;
			generateProductFromRow(row, p);
			regs.push_back(p);
		}
	}

	void Database::addProduct(Product& prod)
	{
		mysqlx::SqlResult result = session->sql("INSERT INTO product (name, price, minQuantity, description) VALUES (?, ?, ?, ?)")
			.bind(prod.name)
			.bind(prod.price)
			.bind(prod.minQuantity)
			.bind(prod.description)
			.execute();
		prod.id = static_cast<int>(result.getAutoIncrementValue());
	}

	void Database::updateProduct(const Product& prod)
	{
		session->sql("UPDATE product SET name = ?, price = ?, minQuantity = ?, description = ? WHERE id = ?")
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
		std::cout << "[Database] closing connection..." << std::endl;
		if(session) session->close();
		delete session;
	}

	void Database::generateRegistryFromRow(const mysqlx::Row& row, Registry& reg)
	{
		reg.id = row[0].get<int>();
		reg.productId = row[1].get<int>();
		reg.type = row[2].get<int>() ? RegistryType::In : RegistryType::Out;
		reg.quantity = row[3].get<int>();
		reg.price = row[4].get<double>();
		reg.total = row[5].get<double>();
		reg.datetime = row[6].get<std::string>();
	}

	void Database::generateProductFromRow(const mysqlx::Row& row, Product& prod)
	{
		prod.id = row[0].get<int>();
		prod.name = row[1].get<std::string>();
		prod.price = row[2].get<double>();
		prod.minQuantity = row[3].get<int>();
		prod.description = row[4].get<std::string>();
	}

}
