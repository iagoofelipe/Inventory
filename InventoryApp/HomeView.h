#pragma once

#include "Database.h"
#include "AppModel.h"

#include <wx/wx.h>
#include <wx/grid.h>
#include <wx/datectrl.h>
#include <wx/dateevt.h>

wxDECLARE_EVENT(EVT_HOMEVIEW_DATE, wxCommandEvent);
wxDECLARE_EVENT(EVT_HOMEVIEW_NEXT, wxCommandEvent);
wxDECLARE_EVENT(EVT_HOMEVIEW_PREV, wxCommandEvent);

namespace inventory
{
	class HomeView : public wxPanel
	{
	public:
		HomeView(wxWindow* parent, wxWindowID id = wxID_ANY);

		void GetDateRange(wxDateTime& start, wxDateTime& end);
		void SetRegistries(const std::vector<Registry*>* regs);
		void SetIntervalLabel(const wxString& text);
		void EnablePrevious(bool enable);
		void EnableNext(bool enable);
		void Clear();

	private:
		AppModel& appModel;

		wxDatePickerCtrl* dtStart;
		wxDatePickerCtrl* dtEnd;
		wxDateTime dtOldStart, dtOldEnd;
		wxGrid* gridProducts;
		wxStaticText* lbGridInfo;
		wxButton* btnPrevious;
		wxButton* btnNext;

		void OnDateStart(wxDateEvent& evt);
		void OnDateEnd(wxDateEvent& evt);
	};
}