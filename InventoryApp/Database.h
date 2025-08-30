#pragma once

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <string>
#include <mysqlx/xdevapi.h>
#include <wx/wx.h>

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

class Database
{
public:
	Database(const Database&) = delete;
	Database& operator=(const Database&) = delete;

	static Database& getInstance();
	bool connect();
	const std::string& getError();

	// Registries
	int getRegistryCount();
	void getRegistryById(int registryId, Registry& reg);
	void getRegistries(std::vector<Registry>& regs);
	void getRegistries(std::vector<Registry>& regs, int limit, int startIndex = 0);
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

	void generateRegistryFromRow(const mysqlx::Row& row, Registry& reg);
	void generateProductFromRow(const mysqlx::Row& row, Product& prod);
};
