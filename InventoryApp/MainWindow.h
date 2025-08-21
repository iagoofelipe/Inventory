#pragma once

#include "MovementRegistryView.h"

#include <wx/wx.h>

class MainWindow : public wxFrame
{
public:
	MainWindow(const wxString& title);

private:
	MovementRegistryView* movementRegistryView;

	void on_movement_saveRequired(wxCommandEvent& event);
	void OnClose(wxCloseEvent& event);
};

