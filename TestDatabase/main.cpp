#include <Database.h>
#include <iostream>

int main() {

	using namespace inventory;

	Database& db = Database::GetInstance();
	DatabaseConnParams params = {
		"localhost",
		33060,
		"inventory_stock",
		"root"
	};

	if (!db.connect(params)) {
		std::cout << "connection error: " << db.getError() << std::endl;
		return 1;
	}

	std::vector<Registry> regs;
	std::vector<Product> prods;
	db.getProducts(prods);
	db.getRegistries(regs);

	for (const auto& p : prods) {
		std::cout
			<< "<Product ID=" << p.id
			<< " Name='" << p.name
			<< "' Price=" << p.price
			<< " minQuantity=" << p.minQuantity
			<< " description='" << p.description << "'"
			<< std::endl;
	}

	for (const auto& r : regs) {

		std::cout
			<< "<Product ID=" << r.id
			<< " productId=" << r.productId
			<< " type=" << r.type
			<< " quantity=" << r.quantity
			<< " price=" << r.price
			<< " total=" << r.total
			<< " datetime='" << r.datetime << "'"
			<< std::endl;
	}

	return 0;
}