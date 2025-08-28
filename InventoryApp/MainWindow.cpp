#include "MainWindow.h"
#include "AppModel.h"

#include <wx/spinctrl.h>
#include <wx/statline.h>

wxDEFINE_EVENT(EVT_VIEW_MOVREG_UPDATED, wxCommandEvent);

MainWindow::MainWindow(const wxString& title)
	: wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600))
	, movementRegistryView(nullptr)
	, productView(nullptr)
	, dashView(nullptr)
	, mainContentPanel(nullptr)
	, currentButton(nullptr)
	, currentContent(__NONE)
{
	SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
	SetBackgroundColour(wxColour());

	wxPanel* navPanel = new wxPanel(this, wxID_ANY);
	btnHome = new wxButton(navPanel, wxID_ANY, "Home");
	btnRegistry = new wxButton(navPanel, wxID_ANY, "Registry");
	btnEditProduct = new wxButton(navPanel, wxID_ANY, "Edit Product");
	btnNewProduct = new wxButton(navPanel, wxID_ANY, "New Product");

	navPanel->SetWindowStyle(wxBORDER_THEME);

	wxBoxSizer* navSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);

	// Navigation Sizer
	wxSizerFlags navFlags = wxSizerFlags().Expand().Border(wxLEFT | wxRIGHT | wxTOP, WIN_SPACE_BETWEEN);
	navSizer->Add(btnHome, navFlags);
	navSizer->Add(btnRegistry, navFlags);
	navSizer->Add(btnEditProduct, navFlags);
	navSizer->Add(btnNewProduct, navFlags);

	navPanel->SetSizer(navSizer);

	// Main Sizer
	sizer->Add(navPanel, 0, wxEXPAND | wxALL, WIN_SPACE_BETWEEN);
	sizer->Add(mainContentPanel = new wxPanel(this), 1, wxEXPAND | wxRIGHT | wxTOP | wxBOTTOM, WIN_SPACE_BETWEEN);

	// Window properties
	SetSizer(sizer);
	SetMinSize(wxSize(800, 600));
	SetSize(wxSize(800, 600));
	Center();

	// Event bindings
	Bind(wxEVT_CLOSE_WINDOW, &MainWindow::OnClose, this);
	btnHome->Bind(wxEVT_BUTTON, [&](wxCommandEvent&) { SetContent(HOME); });
	btnRegistry->Bind(wxEVT_BUTTON, [&](wxCommandEvent&) { SetContent(REGISTRY); });
	btnEditProduct->Bind(wxEVT_BUTTON, [&](wxCommandEvent&) { SetContent(EDIT_PRODUCT); });
	btnNewProduct->Bind(wxEVT_BUTTON, [&](wxCommandEvent&) { SetContent(NEW_PRODUCT); });
}

void MainWindow::SetContent(Content option)
{
	if (currentButton)
		currentButton->Enable();

	// checking if we need to recreate the content
	bool productWasSet = productView != nullptr 
		&& (currentContent == EDIT_PRODUCT || currentContent == NEW_PRODUCT),
		productOption = option == EDIT_PRODUCT || option == NEW_PRODUCT;

	if (!productWasSet || !productOption)
	{
		mainContentPanel->DestroyChildren();
		wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
		wxSizerFlags flags = wxSizerFlags(1).Expand();

		switch (option)
		{
		case HOME:
			currentButton = btnHome;
			sizer->Add(dashView = new DashView(mainContentPanel), flags);
			break;

		case REGISTRY:
			currentButton = btnRegistry;
			sizer->Add(movementRegistryView = new MovementRegistryView(mainContentPanel), flags);
			break;

		case EDIT_PRODUCT:
			currentButton = btnEditProduct;
			sizer->Add(productView = new ProductView(mainContentPanel, wxID_ANY, ProductView::MODE_EDIT), flags);
			break;

		case NEW_PRODUCT:
			currentButton = btnNewProduct;
			sizer->Add(productView = new ProductView(mainContentPanel), flags);
			break;
		}

		mainContentPanel->SetSizer(sizer);
		Layout();
	}
	else
	{
		bool editMode = option == EDIT_PRODUCT;
		ProductView::Mode pvMode = editMode ? ProductView::MODE_EDIT : ProductView::MODE_ADD;
		currentButton = editMode ? btnEditProduct : btnNewProduct;
		
		productView->SetMode(pvMode);
	}

	currentContent = option;
	currentButton->Disable();

	// processing events
	if(option == REGISTRY)
	{
		wxCommandEvent evt(EVT_VIEW_MOVREG_UPDATED, GetId());
		evt.SetClientData(movementRegistryView);
		evt.SetEventObject(this);
		ProcessWindowEvent(evt);
	}
}

MovementRegistryView* MainWindow::GetMovementRegistryView() { return movementRegistryView; }

ProductView* MainWindow::GetProductView() { return productView; }

DashView* MainWindow::GetDashView() { return dashView; }

void MainWindow::OnClose(wxCloseEvent&)
{
	delete pAppModel;
	Destroy();
}