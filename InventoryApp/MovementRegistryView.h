#pragma once

#include "consts.h"

#include <wx/wx.h>

wxDECLARE_EVENT(EVT_MOVREG_SAVE_REQUIRED, wxCommandEvent);

class MovementRegistryView : public wxPanel
{
public:
	MovementRegistryView(wxWindow* parent, wxWindowID id = wxID_ANY);

private:
	void OnClear(wxCommandEvent& event);
	void OnSave(wxCommandEvent& event);
};

