#pragma once

#include <wx/wx.h>
#include "consts.h"

wxDECLARE_EVENT(EVT_CONFIGVIEW_SAVE, wxCommandEvent);

class ConfigView : public wxPanel
{
public:
	ConfigView(wxWindow* parent, wxWindowID id = -1);

	void BlockSignals(bool block);
	void Clear();
	void SetValue(const ConfigParams& cfg);

private:
	wxTextCtrl* txtHost;
	wxSpinCtrl* scPort;
	wxTextCtrl* txtSchema;
	wxTextCtrl* txtUser;
	wxTextCtrl* txtPassword;
	wxButton* btnClear;
	wxButton* btnSave;

	void OnSave(wxCommandEvent& evt);
};

