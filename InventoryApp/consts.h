#pragma once

#include <wx/wx.h>

const int WIN_SPACE_BETWEEN = 10;
const int WIN_MARGIN = 20;

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