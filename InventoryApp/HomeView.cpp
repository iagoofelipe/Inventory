#include "HomeView.h"
#include "consts.h"
#include "tools.h"

#include <wx/statline.h>

wxDEFINE_EVENT(EVT_HOMEVIEW_DATE, wxCommandEvent);
wxDEFINE_EVENT(EVT_HOMEVIEW_NEXT, wxCommandEvent);
wxDEFINE_EVENT(EVT_HOMEVIEW_PREV, wxCommandEvent);

namespace inventory
{
	HomeView::HomeView(wxWindow* parent, wxWindowID id)
		: wxPanel(parent, id)
		, appModel(AppModel::GetInstance())
	{
		const size_t numCols = 6;
		const char* cols[numCols] = { "Product", "Type", "Quantity", "Datetime", "Unit Value", "Total" };
		wxDateTime now = wxDateTime::Now();
		dtOldStart = wxDateTime(1, now.GetMonth(), now.GetYear());
		dtOldEnd = wxDateTime(now.GetLastMonthDay().GetDay(), now.GetMonth(), now.GetYear());

		wxStaticText* lbTitle = new wxStaticText(this, wxID_ANY, "Home");
		wxStaticText* lbTableTitle = new wxStaticText(this, wxID_ANY, "Registries");
		dtStart = new wxDatePickerCtrl(this, wxID_ANY, dtOldStart, wxDefaultPosition, wxDefaultSize, wxDP_DROPDOWN);
		dtEnd = new wxDatePickerCtrl(this, wxID_ANY, dtOldEnd, wxDefaultPosition, wxDefaultSize, wxDP_DROPDOWN);
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
		dtStart->SetRange(REG_DATE_MIN, dtOldEnd);
		dtEnd->SetRange(dtOldStart, REG_DATE_MAX);

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

		// binding events
		btnPrevious->Bind(wxEVT_BUTTON, [&](wxCommandEvent&) { dispatchEvent(EVT_HOMEVIEW_PREV, this); });
		btnNext->Bind(wxEVT_BUTTON, [&](wxCommandEvent&) { dispatchEvent(EVT_HOMEVIEW_NEXT, this); });
		dtStart->Bind(wxEVT_DATE_CHANGED, &HomeView::OnDateStart, this);
		dtEnd->Bind(wxEVT_DATE_CHANGED, &HomeView::OnDateEnd, this);
	}
	void HomeView::GetDateRange(wxDateTime& start, wxDateTime& end)
	{
		start = dtStart->GetValue();
		end = dtEnd->GetValue();
	}

	void HomeView::SetRegistries(const std::vector<Registry*>* regs)
	{
		gridProducts->ClearGrid();

		int row = 0;
		for (const auto& reg : *regs) {
			gridProducts->SetCellValue(row, 0, appModel.GetProductById(reg->productId).name);
			gridProducts->SetCellValue(row, 1, reg->type == RegistryType::In ? "In" : "Out");
			gridProducts->SetCellValue(row, 2, wxString::Format("%d", reg->quantity));
			gridProducts->SetCellValue(row, 3, reg->datetime);
			gridProducts->SetCellValue(row, 4, wxString::Format("$ %.2f", reg->price));
			gridProducts->SetCellValue(row, 5, wxString::Format("$ %.2f", reg->total));
			row++;
		}
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

	void HomeView::Clear() {}

	void HomeView::OnDateStart(wxDateEvent& evt)
	{
		const wxDateTime& dt = evt.GetDate();
		
		if (dt > dtOldEnd) {
			wxMessageBox("The initial date must be minor or equal than the final date", "Validation Error", wxICON_ERROR, this);
			dtStart->SetValue(dtOldStart);
			return;
		}

		dtOldStart = dt;
		dtEnd->SetRange(dt, REG_DATE_MAX);
		dispatchEvent(EVT_HOMEVIEW_DATE, this);
	}

	void HomeView::OnDateEnd(wxDateEvent& evt)
	{
		const wxDateTime& dt = evt.GetDate();

		if (dt < dtOldStart) {
			wxMessageBox("The final date must be major or equal than the initial date", "Validation Error", wxICON_ERROR, this);
			dtEnd->SetValue(dtOldEnd);
			return;
		}

		dtOldEnd = dt;
		dtStart->SetRange(REG_DATE_MIN, dt);
		dispatchEvent(EVT_HOMEVIEW_DATE, this);
	}
}