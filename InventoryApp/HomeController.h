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

	private:
		HomeModel model;
		HomeView* view;
	};
}

