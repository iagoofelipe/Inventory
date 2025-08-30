#pragma once

#include "AppController.h"

#include <wx/wx.h>

class InventoryApp : public wxApp
{
public:
	bool OnInit();

private:
	AppController controller;
};

