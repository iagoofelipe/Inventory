#include "MovementRegistryView.h"
#include "AppModel.h"

#include <wx/spinctrl.h>

wxDEFINE_EVENT(EVT_MOVREG_SAVE_REQUIRED, wxCommandEvent);

MovementRegistryView::MovementRegistryView(wxWindow* parent, wxWindowID id)
	: wxPanel(parent, id)
{
	wxStaticText* lbTitle = new wxStaticText(this, wxID_ANY, "Movement Regitry");
	wxRadioButton* rbIn = new wxRadioButton(this, wxID_ANY, "In");
	wxRadioButton* rbOut = new wxRadioButton(this, wxID_ANY, "Out");
	wxComboBox* cbProduct = new wxComboBox(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, nullptr, wxCB_READONLY);
	wxButton* btnAddProduct = new wxButton(this, wxID_ANY, "add");
	wxSpinCtrl* scQuantity = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 10000);
	wxSpinCtrlDouble* scPrice = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0.0, 1000000.0, 0.0, 0.01);
	wxSpinCtrlDouble* scPriceTotal = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0.0, 1000000.0, 0.0, 0.01);
	wxButton* btnClear = new wxButton(this, wxID_ANY, "clear");
	wxButton* btnSave = new wxButton(this, wxID_ANY, "save");

	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* radioSizer = new wxBoxSizer(wxHORIZONTAL);
	wxFlexGridSizer* gridSizer = new wxFlexGridSizer(2, WIN_SPACE_BETWEEN, WIN_SPACE_BETWEEN);
	wxBoxSizer* productSizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* btnSizer = new wxBoxSizer(wxHORIZONTAL);

	lbTitle->SetFont(wxFont(16, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

	// Panel Sizer
	sizer->Add(lbTitle);
	sizer->AddSpacer(WIN_SPACE_BETWEEN);
	sizer->Add(radioSizer);
	sizer->AddSpacer(WIN_SPACE_BETWEEN);
	sizer->Add(gridSizer, 0, wxEXPAND);
	sizer->AddStretchSpacer();
	sizer->Add(btnSizer, 0, wxEXPAND);

	// Radio Sizer
	radioSizer->Add(rbIn, 0, wxRIGHT, WIN_SPACE_BETWEEN);
	radioSizer->Add(rbOut);

	// Grid Sizer
	gridSizer->AddGrowableCol(1, 1);

	gridSizer->Add(new wxStaticText(this, wxID_ANY, "Product"), 0, wxALIGN_CENTER_VERTICAL);
	gridSizer->Add(productSizer, 0, wxEXPAND);
	gridSizer->Add(new wxStaticText(this, wxID_ANY, "Quantity"), 0, wxALIGN_CENTER_VERTICAL);
	gridSizer->Add(scQuantity, 0, wxEXPAND);
	gridSizer->Add(new wxStaticText(this, wxID_ANY, "Unit Value"), 0, wxALIGN_CENTER_VERTICAL);
	gridSizer->Add(scPrice, 0, wxEXPAND);
	gridSizer->Add(new wxStaticText(this, wxID_ANY, "Total Value"), 0, wxALIGN_CENTER_VERTICAL);
	gridSizer->Add(scPriceTotal, 0, wxEXPAND);

	// Products Sizer
	productSizer->Add(cbProduct, 1, wxRIGHT, WIN_SPACE_BETWEEN);
	productSizer->Add(btnAddProduct);

	// Button Sizer
	btnSizer->AddStretchSpacer();
	btnSizer->Add(btnClear, 0, wxRIGHT, WIN_SPACE_BETWEEN);
	btnSizer->Add(btnSave);

	SetSizer(sizer);

	// Event bindings
	btnClear->Bind(wxEVT_BUTTON, &MovementRegistryView::OnClear, this);
	btnSave->Bind(wxEVT_BUTTON, &MovementRegistryView::OnSave, this);
}

void MovementRegistryView::OnClear(wxCommandEvent& event)
{
	wxMessageBox("Clear button clicked", "Info", wxOK | wxICON_INFORMATION, this);
}

void MovementRegistryView::OnSave(wxCommandEvent& event)
{
	wxCommandEvent evt(EVT_MOVREG_SAVE_REQUIRED, GetId());
	Movement* data = new Movement {
		.productId = -1,
		.isIn = true,
		.quantity = 0,
		.unitValue = 0.0,
		.totalValue = 0.0
	};

	pAppModel->DeleteLater(data);

	evt.SetEventObject(this);
	evt.SetClientData(data);

	ProcessWindowEvent(evt);
}
