#pragma once

#include <wx/wx.h>

const int WIN_SPACE_BETWEEN = 10;

const int MAX_UNIT_VALUE = 1000000;
const int MAX_TOTAL_VALUE = 1000000;
const int MAX_PRODUCT_QUANTITY = 10000;
const int MAX_LEN_TAB_PRODUCTS = 20;

const wxFont TITLE_FONT = wxFont(16, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);

struct Product
{
	int id;
	wxString name;
	double value;
	unsigned int minQuantity;
};

struct Movement
{
	int productId;
	bool isIn;
	unsigned int quantity;
	double unitValue;
	double totalValue;
};