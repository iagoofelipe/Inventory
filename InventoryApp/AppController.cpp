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
	view->SetContent(MainWindow::REGISTRY);

	view->Show();
}

void AppController::on_view_movementRegistryUpdated(wxCommandEvent& event)
{
	MovementRegistryView* movRegView = (MovementRegistryView*)event.GetClientData();
	if (!movRegView)
		return;

	movRegView->Bind(EVT_MOVREG_SAVE_REQUIRED, &AppController::on_movement_saveRequired, this);
}

void AppController::on_movement_saveRequired(wxCommandEvent& event)
{
	Movement* mov = (Movement*)event.GetClientData();

	wxMessageBox(wxString::Format("Movement saved: Product ID %d, Quantity %u, Value %.2f",
		mov->productId, mov->quantity, mov->totalValue), "Movement Saved", wxOK | wxICON_INFORMATION, view);
}