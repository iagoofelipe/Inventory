#include "HomeController.h"

namespace inventory
{
	HomeController::HomeController()
		: view(nullptr)
	{
	}

	HomeController::~HomeController()
	{
	}

	void HomeController::SetView(HomeView* view)
	{
		this->view = view;
		UpdateValues();

		// binding events
		view->Bind(EVT_HOMEVIEW_PREV, &HomeController::on_view_previous, this);
		view->Bind(EVT_HOMEVIEW_NEXT, &HomeController::on_view_next, this);
		view->Bind(EVT_HOMEVIEW_DATE, &HomeController::on_view_date, this);
	}

	void HomeController::UpdateValues()
	{
		wxDateTime start, end;

		view->GetDateRange(start, end);
		model.SetDateRange(start, end);

		if (model.Count()) {
			view->SetRegistries(model.GetValue());
			view->SetIntervalLabel(model.GetLabel());
			view->EnablePrevious(model.HasPrevious());
			view->EnableNext(model.HasNext());
		}
		else {
			view->Clear();
		}
	}

	void HomeController::on_view_previous(wxCommandEvent& evt)
	{
		view->SetRegistries(model.Previous());
		view->EnablePrevious(model.HasPrevious());
		view->EnableNext(model.HasNext());
		view->SetIntervalLabel(model.GetLabel());
	}

	void HomeController::on_view_next(wxCommandEvent& evt)
	{
		view->SetRegistries(model.Next());
		view->EnablePrevious(model.HasPrevious());
		view->EnableNext(model.HasNext());
		view->SetIntervalLabel(model.GetLabel());
	}

	void HomeController::on_view_date(wxCommandEvent& evt)
	{
		UpdateValues();
	}
}