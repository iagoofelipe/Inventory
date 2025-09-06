#pragma once

#include "HomeModel.h"
#include "HomeView.h"

namespace inventory
{
	class HomeController
	{
	public:
		HomeController();
		~HomeController();

		void SetView(HomeView* view);
		void UpdateValues();

	private:
		HomeModel model;
		HomeView* view;

		void on_view_previous(wxCommandEvent& evt);
		void on_view_next(wxCommandEvent& evt);
		void on_view_date(wxCommandEvent& evt);
	};
}

