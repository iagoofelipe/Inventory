#include "AppController.h"
#include "Database.h"

#include <wx/wx.h>

AppController::AppController()
	: model(AppModel::getInstance())
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

//void AppController::on_AppView_movementRegistryUpdated(wxCommandEvent& event)
//{
//	RegistryView* movRegView = (RegistryView*)event.GetClientData();
//	if (!movRegView)
//		return;
//
//	movRegView->Bind(EVT_REGVIEW_SAVE_REQUIRED, &AppController::on_movement_saveRequired, this);
//	movRegView->Bind(EVT_REGVIEW_EDIT, [&](wxCommandEvent&) { view->SetContent(MainWindow::EDIT_PRODUCT); });
//	movRegView->Bind(EVT_REGVIEW_ADD, [&](wxCommandEvent&) { view->SetContent(MainWindow::NEW_PRODUCT); });
//}

//void AppController::on_movement_saveRequired(wxCommandEvent& event)
//{
//	Movement* mov = (Movement*)event.GetClientData();
//	wxString msg = wxString::Format("Movement saved: Product ID %d, Quantity %u, Value %.2f",
//		mov->productId, mov->quantity, mov->totalValue);
//
//	msg += (mov->isIn? ", type IN" : ", type OUT");
//
//	wxMessageBox(msg, "Movement Saved", wxOK | wxICON_INFORMATION, view);
//}

void AppController::on_AppModel_initialized(wxCommandEvent& event)
{
	AppModel::InitializationResult r = (AppModel::InitializationResult)event.GetInt();

	switch (r)
	{
	case AppModel::InitializationResult::ConfigRequired:
		view->SetContent(AppView::CONFIG);
		break;

	case AppModel::InitializationResult::DatabaseError:
	{
		if (view->GetContent() != AppView::LOADING)
			view->SetContent(AppView::LOADING);

		auto loadingView = view->GetLoadingView();
		
		loadingView->SetMessage("It was not possible to connect with database");
		loadingView->SetButtonLabel("connection parameters");
		loadingView->ShowButton();
	}
		break;

	case AppModel::InitializationResult::OK:
		view->SetContent(AppView::MAIN);
		view->GetMainView()->SetContent(MainView::HOME);
		break;
	}
}

void AppController::on_ConfigView_saveRequired(wxCommandEvent& event)
{
	view->GetConfigView()->BlockSignals(true);
	ConfigParams* params = (ConfigParams*) event.GetClientData();
	model.SetConfig(*params);
	model.Initialize();
}

void AppController::on_LoadingView_button(wxCommandEvent&)
{
	view->SetContent(AppView::CONFIG);
	view->GetConfigView()->SetValue(model.GetConfig());
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
