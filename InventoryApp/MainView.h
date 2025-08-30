#pragma once

#include "RegistryView.h"
#include "ProductView.h"
#include "DashView.h"

#include <wx/wx.h>

wxDECLARE_EVENT(EVT_MAINVIEW_CONTENT_CHANGED, wxCommandEvent);

class MainView : public wxPanel
{
public:
	MainView(wxWindow* parent, wxWindowID id = -1);

	enum Content
	{
		__NONE = -1,
		HOME,
		REGISTRY,
		EDIT_PRODUCT,
		NEW_PRODUCT
	};

	void SetContent(Content option);
	RegistryView* GetRegistryView();
	ProductView* GetProductView();
	DashView* GetDashView();

private:
	Content currentContent;

	// views
	RegistryView* registryView;
	ProductView* productView;
	DashView* dashView;

	// components
	wxPanel* mainContentPanel;
	wxButton* currentButton;
	wxButton* btnHome;
	wxButton* btnRegistry;
	wxButton* btnEditProduct;
	wxButton* btnNewProduct;
};

