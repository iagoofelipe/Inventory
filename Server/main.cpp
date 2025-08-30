#include <mysqlx/xdevapi.h>
#include <iostream>
#include <vector>
#include "config.h"
#include "Database.h"

int main()
{
    if (!server::loadConfigFile()) {
		std::cout << "[Config] load error" << std::endl;
		return 1;
    }

    server::Database& db = server::Database::getInstance();
    if (!db.connect()) {
		std::cout << "[Database] connection error: " << db.getError() << std::endl;
        return 1;
    }

	db.test();

	int count;
	server::Product p;
	std::vector<server::Product> products;

	std::cout << "[Database] product count: " << (count = db.getProductCount()) << std::endl;
	db.getProducts(products);

	if (count) {

		for (const auto& prod : products) {
			std::cout
				<< "<Product Id="
				<< prod.id << " Name='"
				<< prod.name << "' Price="
				<< prod.price << " MinQuantity="
				<< prod.minQuantity << " Descrition='"
				<< prod.description << "'/>"
				<< std::endl;
		}

	}
	else {
		std::cout << "[Database] no products in the database" << std::endl;
	}


	return 0;
}