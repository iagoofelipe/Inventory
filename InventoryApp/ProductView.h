#pragma once

#include <wx/wx.h>
#include <wx/spinctrl.h>

wxDECLARE_EVENT(EVT_PROD_SAVE_REQUIRED, wxCommandEvent);

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
	void SetMode(Mode mode);
	Mode GetMode();

private:
	Mode currentMode;

	wxStaticText* lbTitle;
	wxStaticText* lbProduct;
	wxComboBox* cbProduct;
	wxTextCtrl* txtName;
	wxSpinCtrlDouble* scValue;
	wxSpinCtrl* scMinQuantity;
	wxButton* btnClear;
	wxButton* btnSave;

	//void OnClear(wxCommandEvent& event);
	//void OnSave(wxCommandEvent& event);
};

