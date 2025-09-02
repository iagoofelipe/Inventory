#include "HomeView.h"
#include "consts.h"

#include <wx/statline.h>

wxDEFINE_EVENT(EVT_HOMEVIEW_DATE, wxCommandEvent);
wxDEFINE_EVENT(EVT_HOMEVIEW_NEXT, wxCommandEvent);
wxDEFINE_EVENT(EVT_HOMEVIEW_PREV, wxCommandEvent);

namespace inventory
{
	HomeView::HomeView(wxWindow* parent, wxWindowID id)
		: wxPanel(parent, id)
	{
		const size_t numCols = 6;
		const char* cols[numCols] = { "Product", "Type", "Quantity", "Datetime", "Unit Value", "Total" };

		wxStaticText* lbTitle = new wxStaticText(this, wxID_ANY, "Home");
		wxStaticText* lbTableTitle = new wxStaticText(this, wxID_ANY, "Registries");
		dtStart = new wxDatePickerCtrl(this, wxID_ANY);
		dtEnd = new wxDatePickerCtrl(this, wxID_ANY);
		gridProducts = new wxGrid(this, wxID_ANY);
		lbGridInfo = new wxStaticText(this, wxID_ANY, "0 to 0 of 0 item(s)");
		btnPrevious = new wxButton(this, wxID_ANY, "<");
		btnNext = new wxButton(this, wxID_ANY, ">");

		wxFont infoFont = wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);

		// sizers
		wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
		wxBoxSizer* topSizer = new wxBoxSizer(wxHORIZONTAL);
		wxBoxSizer* navGridSizer = new wxBoxSizer(wxHORIZONTAL);

		// Setting properties
		lbTitle->SetFont(TITLE_FONT);
		lbTableTitle->SetFont(TITLE_FONT);
		gridProducts->CreateGrid(MAX_LEN_TAB_PRODUCTS, numCols);
		gridProducts->EnableEditing(false);
		btnPrevious->Enable(false);
		btnNext->Enable(false);
		//gridProducts->HideRowLabels();

		for (int i = 0; i < numCols; i++)
			gridProducts->SetColLabelValue(i, cols[i]);

		// Panel Sizer
		sizer->Add(topSizer, 0, wxEXPAND);
		sizer->AddSpacer(WIN_SPACE_BETWEEN);
		sizer->Add(new wxStaticLine(this), 0, wxEXPAND);
		sizer->AddSpacer(WIN_SPACE_BETWEEN);
		sizer->Add(lbTableTitle);
		sizer->AddSpacer(WIN_SPACE_BETWEEN);
		sizer->Add(gridProducts, 1, wxEXPAND);
		sizer->AddSpacer(WIN_SPACE_BETWEEN);
		sizer->Add(navGridSizer, 0, wxEXPAND);

		// Top Sizer
		topSizer->Add(lbTitle, 0, wxALIGN_CENTER_VERTICAL);
		topSizer->AddStretchSpacer();
		topSizer->Add(dtStart);
		topSizer->Add(new wxStaticText(this, wxID_ANY, "-"), 0, wxRIGHT | wxLEFT, WIN_SPACE_BETWEEN);
		topSizer->Add(dtEnd);

		// Nav Grid Sizer
		navGridSizer->Add(lbGridInfo);
		navGridSizer->AddStretchSpacer();
		navGridSizer->Add(btnPrevious);
		navGridSizer->AddSpacer(WIN_SPACE_BETWEEN);
		navGridSizer->Add(btnNext);

		SetSizer(sizer);
	}
	void HomeView::GetDateRange(wxDateTime& start, wxDateTime& end)
	{
		start = dtStart->GetValue();
		end = dtEnd->GetValue();
	}

	void HomeView::SetRegistries(const std::vector<Registry*>& regs)
	{

	}
	
	void HomeView::SetIntervalLabel(const wxString& text)
	{
		lbGridInfo->SetLabelText(text);
	}
	void HomeView::EnablePrevious(bool enable)
	{
		btnPrevious->Enable(enable);
	}

	void HomeView::EnableNext(bool enable)
	{
		btnNext->Enable(enable);
	}
}