#pragma once

#include <wx/wx.h>

wxDECLARE_EVENT(EVT_LOADINGVIEW_BTN, wxCommandEvent);

class LoadingView : public wxPanel
{
public:
	LoadingView(wxWindow* parent, wxWindowID id = -1);

	void SetMessage(const wxString& msg);
	void ShowButton();
	void HideButton();
	void SetButtonLabel(const wxString& text);

private:
	wxStaticText* lbText;
	wxButton* btn;
	wxBoxSizer* btnSizer;
};

