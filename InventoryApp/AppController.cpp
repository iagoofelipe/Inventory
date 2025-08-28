#include "AppController.h"

#include <wx/wx.h>

AppController::AppController(MainWindow* view)
	: model(pAppModel)
{
	SetView(view);
}

void AppController::SetView(MainWindow* view)
{
	this->view = view;
	if(!view)
		return;

	view->Bind(EVT_VIEW_MOVREG_UPDATED, &AppController::on_view_movementRegistryUpdated, this);
}

void AppController::Initialize()
{
	SetView(new MainWindow("Inventory"));
	view->SetContent(MainWindow::HOME);

	view->Show();
}

void AppController::on_view_movementRegistryUpdated(wxCommandEvent& event)
{
	MovementRegistryView* movRegView = (MovementRegistryView*)event.GetClientData();
	if (!movRegView)
		return;

	movRegView->Bind(EVT_MOVREG_SAVE_REQUIRED, &AppController::on_movement_saveRequired, this);
	movRegView->Bind(EVT_MOVREG_EDIT_REQUIRED, [&](wxCommandEvent&) { view->SetContent(MainWindow::EDIT_PRODUCT); });
	movRegView->Bind(EVT_MOVREG_ADD_REQUIRED, [&](wxCommandEvent&) { view->SetContent(MainWindow::NEW_PRODUCT); });
}

void AppController::on_movement_saveRequired(wxCommandEvent& event)
{
	Movement* mov = (Movement*)event.GetClientData();
	wxString msg = wxString::Format("Movement saved: Product ID %d, Quantity %u, Value %.2f",
		mov->productId, mov->quantity, mov->totalValue);

	msg += (mov->isIn? ", type IN" : ", type OUT");

	wxMessageBox(msg, "Movement Saved", wxOK | wxICON_INFORMATION, view);
}