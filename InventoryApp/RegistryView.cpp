#include "RegistryView.h"
#include "tools.h"

#include <wx/statline.h>

wxDEFINE_EVENT(EVT_REGVIEW_SAVE, wxCommandEvent);
wxDEFINE_EVENT(EVT_REGVIEW_EDIT, wxCommandEvent);
wxDEFINE_EVENT(EVT_REGVIEW_ADD, wxCommandEvent);

namespace inventory
{

	RegistryView::RegistryView(wxWindow* parent, wxWindowID id)
		: wxPanel(parent, id)
		, model(AppModel::getInstance())
	{
		wxStaticText* lbTitle = new wxStaticText(this, wxID_ANY, "Movement Regitry");
		rbIn = new wxRadioButton(this, wxID_ANY, "In");
		rbOut = new wxRadioButton(this, wxID_ANY, "Out");
		cbCurrentDateTime = new wxCheckBox(this, wxID_ANY, "Current date and time");
		cbProduct = new wxComboBox(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, nullptr, wxCB_READONLY);
		btnAdd = new wxButton(this, wxID_ANY, "add");
		btnEdit = new wxButton(this, wxID_ANY, "edit");
		scQuantity = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, MAX_PRODUCT_QUANTITY);
		scPrice = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0.0, MAX_UNIT_VALUE, 0.0, 0.01);
		scPriceTotal = new wxSpinCtrlDouble(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0.0, MAX_TOTAL_VALUE, 0.0, 0.01);
		dpDate = new wxDatePickerCtrl(this, wxID_ANY);
		tpTime = new wxTimePickerCtrl(this, wxID_ANY);
		btnClear = new wxButton(this, wxID_ANY, "clear");
		btnSave = new wxButton(this, wxID_ANY, "save");

		wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
		wxBoxSizer* radioSizer = new wxBoxSizer(wxHORIZONTAL);
		wxFlexGridSizer* gridSizer = new wxFlexGridSizer(2, WIN_SPACE_BETWEEN, WIN_SPACE_BETWEEN);
		wxBoxSizer* productSizer = new wxBoxSizer(wxHORIZONTAL);
		wxBoxSizer* datetimeSizer = new wxBoxSizer(wxHORIZONTAL);
		wxBoxSizer* btnSizer = new wxBoxSizer(wxHORIZONTAL);

		lbTitle->SetFont(TITLE_FONT);

		// Panel Sizer
		sizer->Add(lbTitle);
		sizer->AddSpacer(WIN_SPACE_BETWEEN);
		sizer->Add(new wxStaticLine(this), 0, wxEXPAND);
		sizer->AddSpacer(WIN_SPACE_BETWEEN);
		sizer->Add(radioSizer);
		sizer->AddSpacer(WIN_SPACE_BETWEEN);
		sizer->Add(cbCurrentDateTime, 0, wxEXPAND);
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
		gridSizer->Add(new wxStaticText(this, wxID_ANY, "Date and Time"), 0, wxALIGN_CENTER_VERTICAL);
		gridSizer->Add(datetimeSizer, 0, wxEXPAND);

		// Products Sizer
		productSizer->Add(cbProduct, 1);
		productSizer->Add(btnEdit, 0, wxLEFT | wxRIGHT, WIN_SPACE_BETWEEN);
		productSizer->Add(btnAdd);

		// DateTime Sizer
		datetimeSizer->Add(dpDate, 0, wxRIGHT, WIN_SPACE_BETWEEN);
		datetimeSizer->Add(tpTime);

		// Button Sizer
		btnSizer->AddStretchSpacer();
		btnSizer->Add(btnClear, 0, wxRIGHT, WIN_SPACE_BETWEEN);
		btnSizer->Add(btnSave);

		SetSizer(sizer);

		// Event bindings
		btnClear->Bind(wxEVT_BUTTON, [&](wxCommandEvent&) { Clear(); });
		btnSave->Bind(wxEVT_BUTTON, [&](wxCommandEvent&) { dispatchEvent(EVT_REGVIEW_SAVE, this); });
		btnEdit->Bind(wxEVT_BUTTON, [&](wxCommandEvent&) { dispatchEvent(EVT_REGVIEW_EDIT, this); });
		btnAdd->Bind(wxEVT_BUTTON, [&](wxCommandEvent&) { dispatchEvent(EVT_REGVIEW_ADD, this); });
		cbCurrentDateTime->Bind(wxEVT_CHECKBOX, &RegistryView::OnCurrentDateTimeChecked, this);
		cbProduct->Bind(wxEVT_COMBOBOX, &RegistryView::OnComboProduct, this);

		Clear();
	}

	void RegistryView::Clear()
	{
		rbIn->SetValue(false);
		rbOut->SetValue(true);
		cbCurrentDateTime->SetValue(true);
		scQuantity->SetValue(1);
		scPrice->SetValue(0.0);
		scPriceTotal->SetValue(0.0);
		dpDate->Enable(false);
		tpTime->Enable(false);

		UpdateProducts();
	}

	void RegistryView::SetProduct(const Product& product)
	{
		scPrice->SetValue(product.price);
		scPriceTotal->SetValue(product.price * scQuantity->GetValue());
	}

	void RegistryView::SetProductById(int id)
	{
		SetProduct(model.GetProductById(id));
	}

	void RegistryView::GetValue(Registry& reg)
	{
		wxString
			dt = cbCurrentDateTime->GetValue()
			? wxDateTime::Now().Format("%Y-%m-%d %H:%M:%S")
			: dpDate->GetValue().Format("%Y-%m-%d ") + tpTime->GetValue().Format("%H:%M:%S");

		reg.id = -1;
		reg.productId = GetProductIdSelected();
		reg.type = rbIn->GetValue() ? RegistryType::In : RegistryType::Out;
		reg.quantity = (unsigned int)scQuantity->GetValue();
		reg.price = scPrice->GetValue();
		reg.total = scPriceTotal->GetValue();
		reg.datetime = dt;
	}

	void RegistryView::UpdateProducts()
	{
		cbProduct->Clear();
		const std::vector<Product>& products = model.GetProducts();

		if (!products.size())
			return;

		for (const auto& product : products) {
			cbProduct->Append(product.name, new wxStringClientData(std::to_string(product.id)));
		}

		cbProduct->SetSelection(0);
		SetProduct(products[0]);
	}

	void RegistryView::OnCurrentDateTimeChecked(wxCommandEvent& event)
	{
		bool checked = event.IsChecked();

		if (!checked) {
			wxDateTime dt = wxDateTime::Now();
			dpDate->SetValue(dt);
			tpTime->SetValue(dt);
		}

		dpDate->Enable(!checked);
		tpTime->Enable(!checked);
	}

	void RegistryView::OnComboProduct(wxCommandEvent& event)
	{
		int productId = GetProductIdSelected();
		if (productId == NO_ID) return;
		SetProduct(model.GetProductById(productId));
	}

	int RegistryView::GetProductIdSelected()
	{
		int selection = cbProduct->GetSelection();
		if (selection == wxNOT_FOUND) return NO_ID;

		wxStringClientData* client = (wxStringClientData*)cbProduct->GetClientObject(selection);
		if (client == NULL) return NO_ID;

		return std::stoi(client->GetData().ToStdString());
	}

}