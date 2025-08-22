#pragma once

#include <wx/wx.h>
#include <wx/spinctrl.h>

wxDECLARE_EVENT(EVT_PROD_SAVE_REQUIRED, wxCommandEvent);

class ProductView : public wxPanel
{
public:
	//ProductView(wxWindow* parent, wxWindowID id = wxID_ANY);

	//void Clear();

private:
	wxTextCtrl* txtName;
	wxSpinCtrlDouble* scValue;
	wxSpinCtrl* scMinQuantity;
	wxButton* btnClear;
	wxButton* btnSave;

	//void OnClear(wxCommandEvent& event);
	//void OnSave(wxCommandEvent& event);
};

