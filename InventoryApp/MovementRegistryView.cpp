#include "MovementRegistryView.h"
#include "AppModel.h"

#include <wx/statline.h>

wxDEFINE_EVENT(EVT_MOVREG_SAVE_REQUIRED, wxCommandEvent);
wxDEFINE_EVENT(EVT_MOVREG_EDIT_REQUIRED, wxCommandEvent);
wxDEFINE_EVENT(EVT_MOVREG_ADD_REQUIRED, wxCommandEvent);

MovementRegistryView::MovementRegistryView(wxWindow* parent, wxWindowID id)
	: wxPanel(parent, id)
{
	wxStaticText* lbTitle = new wxStaticText(this, wxID_ANY, "Movement Regitry");
	rbIn = new wxRadioButton(this, wxID_ANY, "In");
	rbOut = new wxRadioButton(this, wxID_ANY, "Out");
	cbProduct = new wxComboBox(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, nullptr, wxCB_READONLY);
	btnAdd = new wxButton(this, wxID_ANY, "add");
	btnEdit = new wxButton(this, wxID_ANY, "edit");
	scQuantity = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, MAX_PRODUCT_QUANTITY);
	scPrice = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0.0, MAX_UNIT_VALUE, 0.0, 0.01);
	scPriceTotal = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0.0, MAX_TOTAL_VALUE, 0.0, 0.01);
	btnClear = new wxButton(this, wxID_ANY, "clear");
	btnSave = new wxButton(this, wxID_ANY, "save");

	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* radioSizer = new wxBoxSizer(wxHORIZONTAL);
	wxFlexGridSizer* gridSizer = new wxFlexGridSizer(2, WIN_SPACE_BETWEEN, WIN_SPACE_BETWEEN);
	wxBoxSizer* productSizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* btnSizer = new wxBoxSizer(wxHORIZONTAL);

	lbTitle->SetFont(TITLE_FONT);

	// Panel Sizer
	sizer->Add(lbTitle);
	sizer->AddSpacer(WIN_SPACE_BETWEEN);
	sizer->Add(new wxStaticLine(this), 0, wxEXPAND);
	sizer->AddSpacer(WIN_SPACE_BETWEEN);
	sizer->Add(radioSizer);
	sizer->AddSpacer(WIN_SPACE_BETWEEN);
	sizer->Add(gridSizer, 1, wxEXPAND);
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
	productSizer->Add(cbProduct, 1);
	productSizer->Add(btnEdit, 0, wxLEFT | wxRIGHT, WIN_SPACE_BETWEEN);
	productSizer->Add(btnAdd);

	// Button Sizer
	btnSizer->AddStretchSpacer();
	btnSizer->Add(btnClear, 0, wxRIGHT, WIN_SPACE_BETWEEN);
	btnSizer->Add(btnSave);

	SetSizer(sizer);

	// Event bindings
	btnClear->Bind(wxEVT_BUTTON, [&](wxCommandEvent&) { Clear(); });
	btnSave->Bind(wxEVT_BUTTON, &MovementRegistryView::OnSave, this);
	btnEdit->Bind(wxEVT_BUTTON, &MovementRegistryView::OnEdit, this);
	btnAdd->Bind(wxEVT_BUTTON, &MovementRegistryView::OnAdd, this);

	rbOut->SetValue(true);
}

void MovementRegistryView::Clear()
{
	rbIn->SetValue(false);
	rbOut->SetValue(true);
	cbProduct->SetSelection(wxNOT_FOUND);
	scQuantity->SetValue(0);
	scPrice->SetValue(0.0);
	scPriceTotal->SetValue(0.0);
}

void MovementRegistryView::OnSave(wxCommandEvent& event)
{
	wxCommandEvent evt(EVT_MOVREG_SAVE_REQUIRED, GetId());
	Movement* data = new Movement {
		.productId = -1,
		.isIn = rbIn->GetValue(),
		.quantity = (unsigned int) scQuantity->GetValue(),
		.unitValue = scPrice->GetValue(),
		.totalValue = scPriceTotal->GetValue()
	};

	pAppModel->DeleteLater(data);

	evt.SetEventObject(this);
	evt.SetClientData(data);

	ProcessWindowEvent(evt);
}

void MovementRegistryView::OnEdit(wxCommandEvent& event)
{
	wxCommandEvent evt(EVT_MOVREG_EDIT_REQUIRED, GetId());
	evt.SetEventObject(this);
	ProcessWindowEvent(evt);
}

void MovementRegistryView::OnAdd(wxCommandEvent& event)
{
	wxCommandEvent evt(EVT_MOVREG_ADD_REQUIRED, GetId());
	evt.SetEventObject(this);
	ProcessWindowEvent(evt);
}