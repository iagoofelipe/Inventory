#pragma once

#include "consts.h"
#include "AppModel.h"

#include <wx/wx.h>
#include <wx/spinctrl.h>
#include <wx/datectrl.h>
#include <wx/timectrl.h>

wxDECLARE_EVENT(EVT_REGVIEW_SAVE, wxCommandEvent);
wxDECLARE_EVENT(EVT_REGVIEW_EDIT, wxCommandEvent);
wxDECLARE_EVENT(EVT_REGVIEW_ADD, wxCommandEvent);
wxDECLARE_EVENT(EVT_REGVIEW_PRODUCT, wxCommandEvent);

namespace inventory
{
	class RegistryView : public wxPanel
	{
	public:
		RegistryView(wxWindow* parent, wxWindowID id = wxID_ANY);

		void Clear();
		void SetProduct(const Product& product);
		void SetProductById(int id);
		void GetValue(Registry& reg);
		int GetProductIdSelected();
		void UpdateProducts();

	private:
		AppModel& model;

		wxRadioButton* rbIn;
		wxRadioButton* rbOut;
		wxCheckBox* cbCurrentDateTime;
		wxComboBox* cbProduct;
		wxButton* btnAdd;
		wxButton* btnEdit;
		wxSpinCtrl* scQuantity;
		wxSpinCtrlDouble* scPrice;
		wxSpinCtrlDouble* scPriceTotal;
		wxButton* btnClear;
		wxButton* btnSave;
		wxDatePickerCtrl* dpDate;
		wxTimePickerCtrl* tpTime;

		void OnCurrentDateTimeChecked(wxCommandEvent& event);
		void OnComboProduct(wxCommandEvent& event);
	};
}