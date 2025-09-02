#include "AppController.h"
#include "Database.h"

#include <wx/wx.h>

namespace inventory
{
	AppController::AppController()
		: model(AppModel::GetInstance())
		, view(nullptr)
	{
		model.Bind(EVT_APPMODEL_INITIALIZED, &AppController::on_AppModel_initialized, this);
	}

	void AppController::Initialize()
	{
		mainController.SetAppView(view = new AppView());

		// binding events
		view->Bind(EVT_APPVIEW_CLOSE, &AppController::on_AppView_close, this);
		view->Bind(EVT_APPVIEW_CONTENT_CHANGED, &AppController::on_AppView_contentChanged, this);

		view->Show();
		view->SetContent(AppView::LOADING);
		model.Initialize();
	}

	void AppController::on_AppModel_initialized(wxCommandEvent& event)
	{
		AppModel::InitializationResult r = (AppModel::InitializationResult)event.GetInt();

		switch (r)
		{
		case AppModel::InitializationResult::OK:
			view->SetContent(AppView::MAIN);
			view->GetMainView()->SetContent(MainView::HOME);
			break;

		default:
			if (view->GetContent() != AppView::LOADING)
				view->SetContent(AppView::LOADING);

			auto loadingView = view->GetLoadingView();

			loadingView->SetMessage(event.GetString());
			loadingView->SetButtonLabel("configuration");
			loadingView->ShowButton();
		}
	}

	void AppController::on_ConfigView_saveRequired(wxCommandEvent& event)
	{
		auto configView = view->GetConfigView();
		DatabaseConnParams params;

		configView->BlockSignals(true);
		configView->GetValue(params);
		model.SetDatabaseConnParams(params);
		model.Initialize();
	}

	void AppController::on_LoadingView_button(wxCommandEvent&)
	{
		view->SetContent(AppView::CONFIG);
		view->GetConfigView()->SetValue(model.GetDatabaseConnParams());
	}

	void AppController::on_AppView_close(wxCommandEvent&)
	{
		view->Destroy();
		view = nullptr;
	}

	void AppController::on_AppView_contentChanged(wxCommandEvent& event)
	{
		AppView::Content content = (AppView::Content)event.GetInt();

		switch (content)
		{
		case AppView::MAIN:
			mainController.SetView(view->GetMainView());
			break;

		case AppView::LOADING:
			view->GetLoadingView()->Bind(EVT_LOADINGVIEW_BTN, &AppController::on_LoadingView_button, this);
			break;

		case AppView::CONFIG:
			view->GetConfigView()->Bind(EVT_CONFIGVIEW_SAVE, &AppController::on_ConfigView_saveRequired, this);
			break;

		default:
			break;
		}
	}
}