#pragma once

#include <wx/wx.h>
#include <wx/grid.h>

namespace inventory
{
	class DashView : public wxPanel
	{
	public:
		DashView(wxWindow* parent, wxWindowID id = wxID_ANY);

	private:
		wxComboBox* cbMonth;
		wxComboBox* cbYear;
		wxStaticText* lbStock;
		wxStaticText* lbProducts;
		wxStaticText* lbValue;
		wxGrid* gridProducts;
		wxStaticText* lbGridInfo;
		wxButton* btnPrevious;
		wxButton* btnNext;
	};
}