#include "LoadingView.h"
#include "consts.h"

wxDEFINE_EVENT(EVT_LOADINGVIEW_BTN, wxCommandEvent);

namespace inventory
{
	LoadingView::LoadingView(wxWindow* parent, wxWindowID id)
		: wxPanel(parent, id)
	{
		lbText = new wxStaticText(this, wxID_ANY, "initializing components...", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL);
		btn = new wxButton(this, wxID_ANY, "try again");

		wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
		btnSizer = new wxBoxSizer(wxHORIZONTAL);

		sizer->AddStretchSpacer();
		sizer->Add(lbText, 0, wxEXPAND);
		sizer->AddSpacer(WIN_SPACE_BETWEEN);
		sizer->Add(btnSizer, 0, wxEXPAND);
		sizer->AddStretchSpacer();

		btnSizer->AddStretchSpacer();
		btnSizer->Add(btn);
		btnSizer->AddStretchSpacer();

		HideButton();
		SetSizer(sizer);

		btn->Bind(wxEVT_BUTTON, [&](wxCommandEvent&) {
			wxCommandEvent evt(EVT_LOADINGVIEW_BTN, GetId());
			evt.SetEventObject(this);
			ProcessWindowEvent(evt);
			});
	}

	void LoadingView::SetMessage(const wxString& msg)
	{
		lbText->SetLabelText(msg);
		Layout();
	}

	void LoadingView::ShowButton()
	{
		btnSizer->Show(true);
		Layout();
	}

	void LoadingView::HideButton()
	{
		btnSizer->Show(false);
		Layout();
	}

	void LoadingView::SetButtonLabel(const wxString& text)
	{
		btn->SetLabelText(text);
	}
}