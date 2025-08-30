#pragma once

#include "AppModel.h"

#include <wx/wx.h>
#include <wx/spinctrl.h>

wxDECLARE_EVENT(EVT_PRODVIEW_SAVE, wxCommandEvent);

namespace inventory
{
	class ProductView : public wxPanel
	{
	public:

		enum Mode {
			__NONE = -1,
			MODE_ADD,
			MODE_EDIT
		};

		ProductView(wxWindow* parent, wxWindowID id = wxID_ANY, Mode mode = MODE_ADD);

		void Clear();
		void UpdateProducts();
		void SetValue(const Product& prod);
		void SetValueById(int id);
		void GetValue(Product& prod);
		void SetMode(Mode mode);
		Mode GetMode() const;
		int GetProductIdSelected();

	private:
		AppModel& model;
		Mode currentMode;
		std::map<int, int> productIndexById;

		wxStaticText* lbTitle;
		wxStaticText* lbProduct;
		wxComboBox* cbProduct;
		wxTextCtrl* txtName;
		wxSpinCtrlDouble* scValue;
		wxSpinCtrl* scMinQuantity;
		wxButton* btnClear;
		wxButton* btnSave;

		void OnComboProduct(wxCommandEvent& event);
		//void OnClear(wxCommandEvent& event);
		//void OnSave(wxCommandEvent& event);
	};
}