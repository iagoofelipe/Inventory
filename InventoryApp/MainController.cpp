#include "MainController.h"

MainController::MainController()
	: model(AppModel::getInstance())
	, appView(nullptr)
	, view(nullptr)
{
}

void MainController::SetAppView(AppView* view)
{
	appView = view;
}

void MainController::SetView(MainView* view)
{
	this->view = view;
	if (!view)
		return;

	view->Bind(EVT_MAINVIEW_CONTENT_CHANGED, &MainController::on_MainView_contentChanged, this);
}

void MainController::on_MainView_contentChanged(wxCommandEvent& evt)
{
	MainView::Content content = (MainView::Content)evt.GetInt();

	switch (content)
	{
	case MainView::HOME:
		break;

	case MainView::REGISTRY:
		view->GetRegistryView()->Bind(EVT_REGVIEW_SAVE, &MainController::on_RegistryView_saveRequired, this);
		break;

	case MainView::EDIT_PRODUCT:
		break;

	case MainView::NEW_PRODUCT:
		break;

	default:
		break;
	}
}

void MainController::on_RegistryView_saveRequired(wxCommandEvent& evt)
{
	Registry reg;
	view->GetRegistryView()->GetValue(reg);

	wxString msg = wxString::Format("Registry saved: Product ID %d, Quantity %u, Value %.2f, Total %u, DateTime %s",
		reg.productId, reg.quantity, reg.price, reg.total, reg.datetime);

	msg += (reg.type == RegistryType::In? ", type IN" : ", type OUT");

	wxMessageBox(msg, "Registry Saved", wxOK | wxICON_INFORMATION, view);
}
