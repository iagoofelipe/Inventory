#pragma once

#include "AppModel.h"
#include "MainWindow.h"

class AppController
{
public:
	AppController(MainWindow* view = nullptr);

	void SetView(MainWindow* view);
	void Initialize();

private:
	MainWindow* view;
	AppModel* model;

	void on_view_movementRegistryUpdated(wxCommandEvent& event);
	void on_movement_saveRequired(wxCommandEvent& event);
};

