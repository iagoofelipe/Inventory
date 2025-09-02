#pragma once

#include "RegistryView.h"
#include "ProductView.h"
#include "HomeView.h"

#include <wx/wx.h>

wxDECLARE_EVENT(EVT_MAINVIEW_CONTENT_CHANGED, wxCommandEvent);

namespace inventory
{
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
		HomeView* GetHomeView();

	private:
		Content currentContent;

		// views
		RegistryView* registryView;
		ProductView* productView;
		HomeView* homeView;

		// components
		wxPanel* mainContentPanel;
		wxButton* currentButton;
		wxButton* btnHome;
		wxButton* btnRegistry;
		wxButton* btnEditProduct;
		wxButton* btnNewProduct;
	};
}