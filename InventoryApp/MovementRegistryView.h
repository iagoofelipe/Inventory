#pragma once

#include "consts.h"

#include <wx/wx.h>
#include <wx/spinctrl.h>
#include <wx/datectrl.h>
#include <wx/timectrl.h>

wxDECLARE_EVENT(EVT_MOVREG_SAVE_REQUIRED, wxCommandEvent);
wxDECLARE_EVENT(EVT_MOVREG_EDIT_REQUIRED, wxCommandEvent);
wxDECLARE_EVENT(EVT_MOVREG_ADD_REQUIRED, wxCommandEvent);

class MovementRegistryView : public wxPanel
{
public:
	MovementRegistryView(wxWindow* parent, wxWindowID id = wxID_ANY);

	void Clear();

private:
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

	void OnSave(wxCommandEvent& event);
	void OnEdit(wxCommandEvent& event);
	void OnAdd(wxCommandEvent& event);
	void OnCurrentDateTimeChecked(wxCommandEvent& event);
};

