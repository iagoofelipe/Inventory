#pragma once

#include "AppModel.h"
#include "AppView.h"
#include "MainView.h"

namespace inventory
{
	class MainController
	{
	public:
		MainController();

		void SetAppView(AppView* view);
		void SetView(MainView* view);

	private:
		AppModel& model;
		AppView* appView;
		MainView* view;

		void on_MainView_contentChanged(wxCommandEvent& evt);
		void on_RegistryView_saveRequired(wxCommandEvent& evt);
		void on_RegistryView_editRequired(wxCommandEvent& evt);
		void on_RegistryView_addRequired(wxCommandEvent& evt);
	};
}