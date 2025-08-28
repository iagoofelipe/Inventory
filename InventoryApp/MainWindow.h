#pragma once

#include "MovementRegistryView.h"
#include "ProductView.h"
#include "DashView.h"

#include <wx/wx.h>

wxDECLARE_EVENT(EVT_VIEW_MOVREG_UPDATED, wxCommandEvent);

class MainWindow : public wxFrame
{
public:
	MainWindow(const wxString& title);

	enum Content
	{
		__NONE = -1,
		HOME,
		REGISTRY,
		EDIT_PRODUCT,
		NEW_PRODUCT
	};

	void SetContent(Content option);
	MovementRegistryView* GetMovementRegistryView();
	ProductView* GetProductView();
	DashView* GetDashView();

private:
	// views
	MovementRegistryView* movementRegistryView;
	ProductView* productView;
	DashView* dashView;

	// components
	wxPanel* mainContentPanel;
	wxButton* currentButton;
	wxButton* btnHome;
	wxButton* btnRegistry;
	wxButton* btnEditProduct;
	wxButton* btnNewProduct;

	// controls
	Content currentContent;

	//void on_movement_saveRequired(wxCommandEvent& event);
	void OnClose(wxCloseEvent& event);
};

