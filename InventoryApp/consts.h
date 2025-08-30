#pragma once

#include <wx/wx.h>

#define CONFIG_FILE "config.ini"
#define DB_DEF_HOST "localhost"
#define DB_DEF_USER "root"
#define DB_DEF_PASSWORD ""
#define DB_DEF_SCHEMA "inventory_stock"

const int DB_DEF_PORT = 33060;

const int WIN_SPACE_BETWEEN = 10;

const int MAX_UNIT_VALUE = 1000000;
const int MAX_TOTAL_VALUE = 1000000;
const int MAX_PRODUCT_QUANTITY = 10000;
const int MAX_LEN_TAB_PRODUCTS = 20;

const wxFont TITLE_FONT = wxFont(16, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);

struct ConfigParams
{
	wxString host;
	int port;
	wxString schema;
	wxString user;
	wxString password;
};

struct _Product
{
	int id;
	wxString name;
	double value;
	unsigned int minQuantity;
};