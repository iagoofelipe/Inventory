#pragma once

#include "AppModel.h"
#include "MainView.h"
#include "LoadingView.h"
#include "ConfigView.h"

#include <wx/wx.h>

wxDECLARE_EVENT(EVT_APPVIEW_CLOSE, wxCommandEvent);
wxDECLARE_EVENT(EVT_APPVIEW_CONTENT_CHANGED, wxCommandEvent);


class AppView : public wxFrame
{
public:

	enum Content
	{
		__NONE = -1,
		MAIN,
		LOADING,
		CONFIG,
	};

	AppView();

	void SetContent(Content option);
	Content GetContent() const;
	MainView* GetMainView();
	LoadingView* GetLoadingView();
	ConfigView* GetConfigView();

private:
	AppModel& model;
	Content currentContent;

	// views
	MainView* mainView;
	LoadingView* loadingView;
	ConfigView* configView;

	static const wxString title;

	void OnClose(wxCloseEvent& event);
};

