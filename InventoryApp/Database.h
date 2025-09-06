#pragma once

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <string>
#include <vector>
#include <mysqlx/xdevapi.h>

namespace inventory
{
	const int NO_ID = -1;

	enum RegistryType {
		Out, In
	};

	struct Product {
		int id;
		std::string name;
		double price;
		int minQuantity;
		std::string description;
	};

	struct Registry {
		int id;
		int productId;
		RegistryType type;
		int quantity;
		double price;
		double total;
		std::string datetime;
	};

	struct DatabaseConnParams
	{
		std::string host;
		int port = 0;
		std::string schema;
		std::string user;
		std::string password;
	};

	class Database
	{
	public:
		Database(const Database&) = delete;
		Database& operator=(const Database&) = delete;

		static Database& GetInstance();
		static const std::vector<std::string> TABLE_COLS_REG;
		static std::string TABLE_COLS_REG_STR;
		static const std::vector<std::string> TABLE_COLS_PROD;
		static std::string TABLE_COLS_PROD_STR;

		bool connect(const DatabaseConnParams& params);
		const std::string& getError();

		// Registries
		int getRegistryCount();
		void getRegistryById(int registryId, Registry& reg);
		void getRegistries(std::vector<Registry>& regs);
		void getRegistries(std::vector<Registry>& regs, int limit, int startIndex = 0);
		void getRegistriesByRange(std::vector<Registry>& regs, const std::string& dtstart, const std::string& dtend);
		void addRegistry(Registry& reg);
		void updateRegistry(const Registry& reg);
		void deleteRegistry(int registryId);

		// Products
		int getProductCount();
		void getProductById(int productId, Product& reg);
		void getProducts(std::vector<Product>& products);
		void getProducts(std::vector<Product>& products, int limit, int startIndex = 0);
		void addProduct(Product& prod);
		void updateProduct(const Product& prod);
		void deleteProduct(int productId);

	private:
		Database();
		~Database();

		mysqlx::Session* session;
		std::string error;


		void registryFromRow(const mysqlx::Row& row, Registry& reg);
		void registryFromRow(const std::vector<mysqlx::Row>& rows, std::vector<Registry>& regs);
		void productFromRow(const mysqlx::Row& row, Product& prod);
		void productFromRow(const std::vector<mysqlx::Row>& rows, std::vector<Product>& prods);
		
		/*
		Generate the fields to a sql query

		result: ?, ?, ..., ?
		result with keyValue: val1 = ?, val2 = ?

		*/
		std::string getPlaceHolderFromTable(const std::vector<std::string>& cols, bool keyValue = false, bool ignoreId = false);
	};
}