#include "ProductView.h"
#include "consts.h"
#include "tools.h"

#include <wx/statline.h>

wxDEFINE_EVENT(EVT_PRODVIEW_SAVE, wxCommandEvent);

namespace inventory
{
	ProductView::ProductView(wxWindow* parent, wxWindowID id, Mode mode)
		: wxPanel(parent, id)
		, currentMode(__NONE)
		, model(AppModel::GetInstance())
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

		cbProduct->Bind(wxEVT_COMBOBOX, &ProductView::OnComboProduct, this);
		btnClear->Bind(wxEVT_BUTTON, [&](wxCommandEvent&) { Clear(); });
		btnSave->Bind(wxEVT_BUTTON, [&](wxCommandEvent&) { dispatchEvent(EVT_PRODVIEW_SAVE, this); });

		SetSizer(sizer);
		SetMode(mode);
	}

	void ProductView::Clear()
	{
		cbProduct->SetSelection(wxNOT_FOUND);
		txtName->Clear();
		scValue->SetValue(0);
		scMinQuantity->SetValue(0);

		UpdateProducts();
	}

	void ProductView::UpdateProducts()
	{
		cbProduct->Clear();
		productIndexById.clear();

		const std::vector<Product>& products = model.GetProducts();

		if (!products.size())
			return;

		int index = 0;
		for (const auto& product : products) {
			productIndexById[product.id] = index++;
			cbProduct->Append(product.name, new wxStringClientData(std::to_string(product.id)));
		}

		if (currentMode == MODE_EDIT) {
			cbProduct->SetSelection(0);
			SetValue(products[0]);
		}
	}

	void ProductView::SetValue(const Product& prod)
	{
		if (GetProductIdSelected() != prod.id)
			cbProduct->SetSelection(productIndexById[prod.id]);

		txtName->SetValue(prod.name);
		scValue->SetValue(prod.price);
		scMinQuantity->SetValue(prod.minQuantity);
	}

	void ProductView::SetValueById(int id)
	{
		SetValue(model.GetProductById(id));
	}

	void ProductView::GetValue(Product& prod)
	{
		prod.id = currentMode == MODE_EDIT ? GetProductIdSelected() : NO_ID;
		prod.name = txtName->GetValue();
		prod.price = scValue->GetValue();
		prod.minQuantity = scMinQuantity->GetValue();
	}

	void ProductView::SetMode(Mode mode)
	{
		if (currentMode == mode)
			return;

		currentMode = mode;
		bool edit = mode == MODE_EDIT;

		lbProduct->Show(edit);
		cbProduct->Show(edit);
		lbTitle->SetLabel(edit ? "Edit Product" : "Add Product");

		Clear();
		Layout();
	}

	ProductView::Mode ProductView::GetMode() const
	{
		return currentMode;
	}

	int ProductView::GetProductIdSelected()
	{
		int selection = cbProduct->GetSelection();
		if (selection == wxNOT_FOUND) return NO_ID;

		wxStringClientData* client = (wxStringClientData*)cbProduct->GetClientObject(selection);
		if (client == NULL) return NO_ID;

		return std::stoi(client->GetData().ToStdString());
	}

	void ProductView::OnComboProduct(wxCommandEvent& event)
	{
		int productId = GetProductIdSelected();
		if (productId == NO_ID) return;
		SetValue(model.GetProductById(productId));
	}
}