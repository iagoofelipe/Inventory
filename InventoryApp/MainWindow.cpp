#include "MainWindow.h"
#include "AppModel.h"

#include <wx/spinctrl.h>

MainWindow::MainWindow(const wxString& title)
	: wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600))
{
	SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
	SetBackgroundColour(wxColour());

	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(movementRegistryView = new MovementRegistryView(this), 1, wxEXPAND | wxALL, WIN_MARGIN);

	// Window properties
	SetSizer(sizer);
	SetMinSize(wxSize(800, 600));
	SetSize(wxSize(800, 600));
	Center();

	// Event bindings
	Bind(EVT_MOVREG_SAVE_REQUIRED, &MainWindow::on_movement_saveRequired, this);
	Bind(wxEVT_CLOSE_WINDOW, &MainWindow::OnClose, this);
}

void MainWindow::on_movement_saveRequired(wxCommandEvent& event)
{
	Movement* mov = (Movement*) event.GetClientData();

	wxMessageBox(wxString::Format("Movement saved: Product ID %d, Quantity %u, Value %.2f",
		mov->productId, mov->quantity, mov->totalValue), "Movement Saved", wxOK | wxICON_INFORMATION, this);

	DestroyChildren();

	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

	sizer->AddStretchSpacer();
	sizer->Add(new wxStaticText(this, wxID_ANY, "Novo conteúdo"), 0, wxALIGN_CENTER_HORIZONTAL);
	sizer->Add(new wxButton(this, wxID_ANY, "Clique aqui"));
	sizer->AddStretchSpacer();

	SetSizer(sizer);
	Layout();
}

void MainWindow::OnClose(wxCloseEvent& event)
{
	delete pAppModel;
	Destroy();
}
