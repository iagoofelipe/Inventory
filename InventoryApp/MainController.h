#pragma once

#include "AppModel.h"
#include "AppView.h"
#include "MainView.h"
#include "HomeController.h"

namespace inventory
{
	class MainController
	{
	public:
		MainController();

		void SetView(MainView* view);

	private:
		AppModel& model;
		MainView* view;

		// children
		HomeController homeController;

		void on_MainView_contentChanged(wxCommandEvent& evt);
		void on_RegistryView_saveRequired(wxCommandEvent& evt);
		void on_RegistryView_editRequired(wxCommandEvent& evt);
		void on_RegistryView_addRequired(wxCommandEvent& evt);
	};
}