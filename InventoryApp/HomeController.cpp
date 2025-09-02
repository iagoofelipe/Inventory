#include "HomeController.h"

namespace inventory
{
	HomeController::HomeController()
	{
	}

	HomeController::~HomeController()
	{
	}

	void HomeController::SetView(HomeView* view)
	{
		this->view = view;
		wxDateTime start, end;

		view->GetDateRange(start, end);
		const std::vector<Registry*>* regs = model.GetRegistries(start, end);

		if (regs->size()) {

		}
		else {
			view->Clear();
		}

		// binding events
	}
}