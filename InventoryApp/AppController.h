#pragma once

#include "AppModel.h"
#include "AppView.h"
#include "MainController.h"

class AppController
{
public:
	AppController();

	void Initialize();

private:
	AppModel& model;
	AppView* view;
	MainController mainController;

	// void on_AppView_movementRegistryUpdated(wxCommandEvent& event);
	// void on_movement_saveRequired(wxCommandEvent& event);

	void on_AppModel_initialized(wxCommandEvent& event);
	
	void on_ConfigView_saveRequired(wxCommandEvent& event);
	void on_LoadingView_button(wxCommandEvent& event);

	void on_AppView_close(wxCommandEvent& event);
	void on_AppView_contentChanged(wxCommandEvent& event);
};

