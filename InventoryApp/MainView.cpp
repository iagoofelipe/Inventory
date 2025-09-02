#include "MainView.h"

wxDEFINE_EVENT(EVT_MAINVIEW_CONTENT_CHANGED, wxCommandEvent);

namespace inventory
{
	MainView::MainView(wxWindow* parent, wxWindowID id)
		: wxPanel(parent, id)
		, currentContent(__NONE)
		, registryView(nullptr)
		, productView(nullptr)
		, homeView(nullptr)
		, mainContentPanel(nullptr)
		, currentButton(nullptr)
	{
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

		// Main Sizer
		sizer->Add(navPanel, 0, wxEXPAND);
		sizer->AddSpacer(WIN_SPACE_BETWEEN);
		sizer->Add(mainContentPanel = new wxPanel(this), 1, wxEXPAND);

		// Event bindings
		btnHome->Bind(wxEVT_BUTTON, [&](wxCommandEvent&) { SetContent(HOME); });
		btnRegistry->Bind(wxEVT_BUTTON, [&](wxCommandEvent&) { SetContent(REGISTRY); });
		btnEditProduct->Bind(wxEVT_BUTTON, [&](wxCommandEvent&) { SetContent(EDIT_PRODUCT); });
		btnNewProduct->Bind(wxEVT_BUTTON, [&](wxCommandEvent&) { SetContent(NEW_PRODUCT); });

		// Setting sizers
		navPanel->SetSizer(navSizer);
		SetSizer(sizer);
	}

	void MainView::SetContent(Content option)
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
				sizer->Add(homeView = new HomeView(mainContentPanel), flags);
				break;

			case REGISTRY:
				currentButton = btnRegistry;
				sizer->Add(registryView = new RegistryView(mainContentPanel), flags);
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

		currentButton->Disable();
		currentContent = option;

		wxCommandEvent evt(EVT_MAINVIEW_CONTENT_CHANGED, GetId());
		evt.SetEventObject(this);
		evt.SetInt(option);
		ProcessWindowEvent(evt);
	}

	RegistryView* MainView::GetRegistryView() { return registryView; }

	ProductView* MainView::GetProductView() { return productView; }

	HomeView* MainView::GetHomeView() { return homeView; }
}