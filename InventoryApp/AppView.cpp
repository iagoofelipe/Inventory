#include "AppView.h"
#include "consts.h"
#include "tools.h"


wxDEFINE_EVENT(EVT_APPVIEW_CLOSE, wxCommandEvent);
wxDEFINE_EVENT(EVT_APPVIEW_CONTENT_CHANGED, wxCommandEvent);

namespace inventory
{
	const wxString AppView::title = "Inventory";

	AppView::AppView()
		: wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600))
		, model(AppModel::GetInstance())
		, currentContent(__NONE)
		, mainView(nullptr)
		, loadingView(nullptr)
		, configView(nullptr)
	{
		SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
		SetBackgroundColour(wxColour());

		Bind(wxEVT_CLOSE_WINDOW, [&](wxCloseEvent&) { dispatchEvent(EVT_APPVIEW_CLOSE, this); });

		// Window properties
		SetMinSize(wxSize(800, 600));
		SetSize(wxSize(800, 600));
		Center();
	}

	void AppView::SetContent(Content option)
	{
		if (currentContent == option)
			return;

		DestroyChildren();
		wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
		wxSizerFlags flags = wxSizerFlags(1).Expand().Border(wxALL, WIN_SPACE_BETWEEN);

		switch (option)
		{
		case MAIN:
			sizer->Add(mainView = new MainView(this), flags);
			break;

		case LOADING:
			sizer->Add(loadingView = new LoadingView(this), flags);
			break;

		case CONFIG:
			sizer->Add(configView = new ConfigView(this), flags);
			break;
		}

		SetSizer(sizer);
		Layout();

		currentContent = option;
		int value = option;
		dispatchEvent(EVT_APPVIEW_CONTENT_CHANGED, this, nullptr, &value);
	}

	AppView::Content AppView::GetContent() const
	{
		return currentContent;
	}

	MainView* AppView::GetMainView()
	{
		return currentContent == MAIN ? mainView : nullptr;
	}

	LoadingView* AppView::GetLoadingView()
	{
		return currentContent == LOADING ? loadingView : nullptr;
	}

	ConfigView* AppView::GetConfigView()
	{
		return currentContent == CONFIG ? configView : nullptr;
	}
}