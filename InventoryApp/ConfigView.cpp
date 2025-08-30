#include "ConfigView.h"
#include "consts.h"

#include "AppModel.h"

#include <wx/spinctrl.h>

wxDEFINE_EVENT(EVT_CONFIGVIEW_SAVE, wxCommandEvent);

ConfigView::ConfigView(wxWindow* parent, wxWindowID id)
	: wxPanel(parent, id)
{
	wxStaticText* lbTitle = new wxStaticText(this, wxID_ANY, "Configuration View");
	txtHost = new wxTextCtrl(this, wxID_ANY, DB_DEF_HOST);
	scPort = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 99999);
	txtSchema = new wxTextCtrl(this, wxID_ANY, DB_DEF_SCHEMA);
	txtUser = new wxTextCtrl(this, wxID_ANY, DB_DEF_USER);
	txtPassword = new wxTextCtrl(this, wxID_ANY, DB_DEF_PASSWORD, wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);
	btnClear = new wxButton(this, wxID_ANY, "clear");
	btnSave = new wxButton(this, wxID_ANY, "save");

	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	wxFlexGridSizer* gridSizer = new wxFlexGridSizer(2, WIN_SPACE_BETWEEN, WIN_SPACE_BETWEEN);
	wxBoxSizer* btnSizer = new wxBoxSizer(wxHORIZONTAL);
	
	lbTitle->SetFont(TITLE_FONT);
	scPort->SetValue(DB_DEF_PORT);
	gridSizer->AddGrowableCol(1, 1);

	// Sizer
	sizer->Add(lbTitle);
	sizer->AddSpacer(WIN_SPACE_BETWEEN);
	sizer->Add(new wxStaticText(this, wxID_ANY, "setting up database parameters"));
	sizer->AddSpacer(WIN_SPACE_BETWEEN);
	sizer->Add(gridSizer, 1, wxEXPAND);
	sizer->AddSpacer(WIN_SPACE_BETWEEN);
	sizer->Add(btnSizer, 0, wxEXPAND);

	// Grid Sizer
	gridSizer->Add(new wxStaticText(this, wxID_ANY, "Host"));
	gridSizer->Add(txtHost, 0, wxEXPAND);
	gridSizer->Add(new wxStaticText(this, wxID_ANY, "Port"));
	gridSizer->Add(scPort, 0, wxEXPAND);
	gridSizer->Add(new wxStaticText(this, wxID_ANY, "Database"));
	gridSizer->Add(txtSchema, 0, wxEXPAND);
	gridSizer->Add(new wxStaticText(this, wxID_ANY, "User"));
	gridSizer->Add(txtUser, 0, wxEXPAND);
	gridSizer->Add(new wxStaticText(this, wxID_ANY, "Password"));
	gridSizer->Add(txtPassword, 0, wxEXPAND);

	// Buttons Sizer
	btnSizer->AddStretchSpacer();
	btnSizer->Add(btnClear);
	btnSizer->AddSpacer(WIN_SPACE_BETWEEN);
	btnSizer->Add(btnSave);

	SetSizer(sizer);

	btnClear->Bind(wxEVT_BUTTON, [&](wxCommandEvent&) { Clear(); });
	btnSave->Bind(wxEVT_BUTTON, &ConfigView::OnSave, this);
}

void ConfigView::BlockSignals(bool block)
{
	txtHost->Enable(!block);
	scPort->Enable(!block);
	txtSchema->Enable(!block);
	txtUser->Enable(!block);
	txtPassword->Enable(!block);
	btnClear->Enable(!block);
	btnSave->Enable(!block);
}

void ConfigView::Clear()
{
	txtHost->SetValue(DB_DEF_HOST);
	scPort->SetValue(DB_DEF_PORT);
	txtSchema->SetValue(DB_DEF_SCHEMA);
	txtUser->SetValue(DB_DEF_USER);
	txtPassword->SetValue(DB_DEF_PASSWORD);
}

void ConfigView::SetValue(const ConfigParams& cfg)
{
	txtHost->SetValue(cfg.host);
	scPort->SetValue(cfg.port);
	txtSchema->SetValue(cfg.schema);
	txtUser->SetValue(cfg.user);
	txtPassword->SetValue(cfg.password);
}

void ConfigView::OnSave(wxCommandEvent&)
{
	wxCommandEvent evt(EVT_CONFIGVIEW_SAVE, GetId());
	ConfigParams* params = new ConfigParams {
		txtHost->GetValue(),
		scPort->GetValue(),
		txtSchema->GetValue(),
		txtUser->GetValue(),
		txtPassword->GetValue()
	};

	AppModel::DeleteLater(params);
	evt.SetEventObject(this);
	evt.SetClientData(params);
	ProcessWindowEvent(evt);
}