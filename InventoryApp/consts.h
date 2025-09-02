#pragma once

#include <wx/font.h>
#include <string>

namespace inventory
{
	const int DB_DEF_PORT = 33060;
	const std::string DB_DEF_HOST = "localhost";
	const std::string DB_DEF_USER = "root";
	const std::string DB_DEF_PASSWORD = "";
	const std::string DB_DEF_SCHEMA = "inventory_stock";

	const int WIN_SPACE_BETWEEN = 10;

	const int MAX_UNIT_VALUE = 1000000;
	const int MAX_TOTAL_VALUE = 1000000;
	const int MAX_PRODUCT_QUANTITY = 10000;
	const int MAX_LEN_TAB_PRODUCTS = 20;

	const wxFont TITLE_FONT = wxFont(16, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);

	struct DatabaseConnParams
	{
		std::string host;
		int port = 0;
		std::string schema;
		std::string user;
		std::string password;
	};
}