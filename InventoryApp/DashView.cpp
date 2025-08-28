#include "DashView.h"
#include "consts.h"

#include <wx/statline.h>

DashView::DashView(wxWindow* parent, wxWindowID id)
	: wxPanel(parent, id)
{
	const size_t numCols = 5;
	const char* cols[numCols] = { "Name", "Unit Value", "Quantity", "Minimum Quantity", "Total Value" };

	wxStaticText* lbTitle = new wxStaticText(this, wxID_ANY, "Dashboard");
	cbMonth = new wxComboBox(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, nullptr, wxCB_READONLY);
	cbYear = new wxComboBox(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, nullptr, wxCB_READONLY);
	lbStock = new wxStaticText(this, wxID_ANY, "0");
	lbProducts = new wxStaticText(this, wxID_ANY, "0");
	lbValue = new wxStaticText(this, wxID_ANY, "0");
	gridProducts = new wxGrid(this, wxID_ANY);
	lbGridInfo = new wxStaticText(this, wxID_ANY, "0 to 0 of 0 item(s)");
	btnPrevious = new wxButton(this, wxID_ANY, "<");
	btnNext = new wxButton(this, wxID_ANY, ">");

	wxStaticText* titleLbStock = new wxStaticText(this, wxID_ANY, "Low stock");
	wxStaticText* titleLbProducts = new wxStaticText(this, wxID_ANY, "Total Products");
	wxStaticText* titleLbValue = new wxStaticText(this, wxID_ANY, "Total Value");

	wxFont infoFont = wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);

	// sizers
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* topSizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* infoSizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* navGridSizer = new wxBoxSizer(wxHORIZONTAL);

	// sizers for info
	wxBoxSizer* stockSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* productsSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* valueSizer = new wxBoxSizer(wxVERTICAL);

	// Setting properties
	lbTitle->SetFont(TITLE_FONT);
	titleLbStock->SetFont(infoFont);
	titleLbProducts->SetFont(infoFont);
	titleLbValue->SetFont(infoFont);
	gridProducts->CreateGrid(MAX_LEN_TAB_PRODUCTS, numCols);
	gridProducts->EnableEditing(false);
	btnPrevious->Enable(false);
	btnNext->Enable(false);
	//gridProducts->HideRowLabels();
	
	for(int i = 0; i < numCols; i++)
		gridProducts->SetColLabelValue(i, cols[i]);

	// Panel Sizer
	sizer->Add(topSizer, 0, wxEXPAND);
	sizer->AddSpacer(WIN_SPACE_BETWEEN);
	sizer->Add(new wxStaticLine(this), 0, wxEXPAND);
	sizer->AddSpacer(WIN_SPACE_BETWEEN);
	sizer->Add(infoSizer, 0, wxEXPAND);
	sizer->AddSpacer(WIN_SPACE_BETWEEN);
	sizer->Add(gridProducts, 1, wxEXPAND);
	sizer->AddSpacer(WIN_SPACE_BETWEEN);
	sizer->Add(navGridSizer, 0, wxEXPAND);

	// Top Sizer
	topSizer->Add(lbTitle, 0, wxALIGN_CENTER_VERTICAL);
	topSizer->AddStretchSpacer();
	topSizer->Add(cbMonth);
	topSizer->Add(new wxStaticText(this, wxID_ANY, "/"), 0, wxRIGHT | wxLEFT, WIN_SPACE_BETWEEN);
	topSizer->Add(cbYear);

	// Info Sizer
	infoSizer->Add(stockSizer, 1);
	infoSizer->AddSpacer(WIN_SPACE_BETWEEN);
	infoSizer->Add(valueSizer, 1);
	infoSizer->AddSpacer(WIN_SPACE_BETWEEN);
	infoSizer->Add(productsSizer, 1);

	wxSizerFlags flags = wxSizerFlags().Border(wxBOTTOM, WIN_SPACE_BETWEEN);

	stockSizer->Add(titleLbStock, flags);
	stockSizer->Add(lbStock);

	valueSizer->Add(titleLbProducts, flags);
	valueSizer->Add(lbProducts);

	productsSizer->Add(titleLbValue, flags);
	productsSizer->Add(lbValue);

	// Nav Grid Sizer
	navGridSizer->Add(lbGridInfo);
	navGridSizer->AddStretchSpacer();
	navGridSizer->Add(btnPrevious);
	navGridSizer->AddSpacer(WIN_SPACE_BETWEEN);
	navGridSizer->Add(btnNext);

	SetSizer(sizer);
}
