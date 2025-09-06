#pragma once

#include <wx/font.h>
#include <wx/datetime.h>
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

	const wxDateTime REG_DATE_MIN = wxDateTime(1, wxDateTime::Jan, 2000);
	const wxDateTime REG_DATE_MAX = wxDateTime(31, wxDateTime::Dec, wxDateTime::Now().GetYear() + 100);

	const wxFont TITLE_FONT = wxFont(16, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
}