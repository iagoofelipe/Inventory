#pragma once

#include "MovementRegistryView.h"

#include <wx/wx.h>

wxDECLARE_EVENT(EVT_VIEW_MOVREG_UPDATED, wxCommandEvent);

class MainWindow : public wxFrame
{
public:
	MainWindow(const wxString& title);

	enum Content
	{
		HOME,
		REGISTRY,
		EDIT_PRODUCT,
		NEW_PRODUCT
	};

	void SetContent(Content option);
	MovementRegistryView* GetMovementRegistryView(MovementRegistryView* view);

private:
	MovementRegistryView* movementRegistryView;
	wxPanel* mainContentPanel;
	wxButton* currentButton;
	wxButton* btnHome;
	wxButton* btnRegistry;
	wxButton* btnEditProduct;
	wxButton* btnNewProduct;

	//void on_movement_saveRequired(wxCommandEvent& event);
	void OnClose(wxCloseEvent& event);
};

