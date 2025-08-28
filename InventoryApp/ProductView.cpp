#include "ProductView.h"
#include "consts.h"

#include <wx/statline.h>

wxDEFINE_EVENT(EVT_PROD_SAVE_REQUIRED, wxCommandEvent);

ProductView::ProductView(wxWindow* parent, wxWindowID id, Mode mode)
	: wxPanel(parent, id)
	, currentMode(__NONE)
{
	lbTitle = new wxStaticText(this, wxID_ANY, wxEmptyString);
	lbProduct = new wxStaticText(this, wxID_ANY, "Product");
	cbProduct = new wxComboBox(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, nullptr, wxCB_READONLY);
	txtName = new wxTextCtrl(this, wxID_ANY);
	scValue = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, MAX_UNIT_VALUE, 0, 0.01);
	scMinQuantity = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, MAX_PRODUCT_QUANTITY);
	btnClear = new wxButton(this, wxID_ANY, "clear");
	btnSave = new wxButton(this, wxID_ANY, "save");

	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	wxFlexGridSizer* gridSizer = new wxFlexGridSizer(2, WIN_SPACE_BETWEEN, WIN_SPACE_BETWEEN);
	wxBoxSizer* btnSizer = new wxBoxSizer(wxHORIZONTAL);

	lbTitle->SetFont(TITLE_FONT);

	// Panel Sizer
	sizer->Add(lbTitle);
	sizer->AddSpacer(WIN_SPACE_BETWEEN);
	sizer->Add(new wxStaticLine(this), 0, wxEXPAND);
	sizer->AddSpacer(WIN_SPACE_BETWEEN);
	sizer->Add(gridSizer, 1, wxEXPAND);
	sizer->AddStretchSpacer();
	sizer->Add(btnSizer, 0, wxEXPAND);

	// Grid Sizer
	gridSizer->AddGrowableCol(1, 1);

	gridSizer->Add(lbProduct, 0, wxALIGN_CENTER_VERTICAL);
	gridSizer->Add(cbProduct, 0, wxEXPAND);
	gridSizer->Add(new wxStaticText(this, wxID_ANY, "Name"), 0, wxALIGN_CENTER_VERTICAL);
	gridSizer->Add(txtName, 0, wxEXPAND);
	gridSizer->Add(new wxStaticText(this, wxID_ANY, "Unit Value"), 0, wxALIGN_CENTER_VERTICAL);
	gridSizer->Add(scValue, 0, wxEXPAND);
	gridSizer->Add(new wxStaticText(this, wxID_ANY, "Minimum Quantity"), 0, wxALIGN_CENTER_VERTICAL);
	gridSizer->Add(scMinQuantity, 0, wxEXPAND);

	// Button Sizer
	btnSizer->AddStretchSpacer();
	btnSizer->Add(btnClear, 0, wxRIGHT, WIN_SPACE_BETWEEN);
	btnSizer->Add(btnSave);

	SetSizer(sizer);
	SetMode(mode);

}

void ProductView::Clear()
{
	cbProduct->SetSelection(wxNOT_FOUND);
	txtName->SetValue(wxEmptyString);
	scMinQuantity->SetValue(0);
}

void ProductView::SetMode(Mode mode)
{
	if(currentMode == mode)
		return;

	currentMode = mode;
	bool edit = mode == MODE_EDIT;
	
	lbProduct->Show(edit);
	cbProduct->Show(edit);
	lbTitle->SetLabel(edit ? "Edit Product" : "Add Product");

	Layout();
}

ProductView::Mode ProductView::GetMode()
{
	return currentMode;
}