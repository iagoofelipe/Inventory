#include "AppModel.h"
#include "config.h"

#include <wx/wx.h>
#include <wx/log.h>

#include <thread>
#include <chrono>

wxDEFINE_EVENT(EVT_APPMODEL_INITIALIZED, wxCommandEvent);
wxDEFINE_EVENT(EVT_APPMODEL_REGS_UPDATED, wxCommandEvent);
wxDEFINE_EVENT(EVT_APPMODEL_PRODUCTS_UPDATED, wxCommandEvent);

bool AppModel::cleaned = false;
std::vector<ConfigParams*> AppModel::toDelete_ConfigParams{};
ConfigParams AppModel::cfg{};
std::ofstream* AppModel::logFile = new std::ofstream("app.log", std::ios::app);

AppModel& AppModel::getInstance()
{
	static AppModel instance;
	return instance;
}

void AppModel::Initialize()
{
	wxLog::SetActiveTarget(new wxLogStream(logFile));

	std::thread t(&AppModel::_initialize, this);
	t.detach();
}

void AppModel::UpdateValues()
{
	db.getProducts(products);
	db.getRegistries(regs);

	regsById.clear();
	productsById.clear();

	for (Product& p : products) productsById[p.id] = &p;
	for (Registry& r : regs) regsById[r.id] = &r;
}

const std::vector<Registry>& AppModel::GetRegistries()
{
	return regs;
}

const std::vector<Product>& AppModel::GetProducts()
{
	return products;
}

const Registry& AppModel::GetRegistryById(int id)
{
	return *regsById[id];
}

const Product& AppModel::GetProductById(int id)
{
	return *productsById[id];
}

void AppModel::DeleteLater(ConfigParams* obj)
{
	toDelete_ConfigParams.push_back(obj);
}

void AppModel::Release()
{
	if (cleaned)
		return;

	cleaned = true;
	delete logFile;

	// deleting pointers
	for (auto ptr : toDelete_ConfigParams) delete ptr;

	toDelete_ConfigParams.clear();
}

ConfigParams AppModel::GetConfig()
{
	return cfg;
}

void AppModel::SetConfig(const ConfigParams& cfg)
{
	AppModel::cfg = cfg;

	setConfig("host", cfg.host.ToStdString());
	setConfig("port", std::to_string(cfg.port));
	setConfig("user", cfg.user.ToStdString());
	setConfig("password", cfg.password.ToStdString());
	setConfig("database", cfg.schema.ToStdString());
	updateConfigFile();
}

AppModel::AppModel()
	: wxEvtHandler()
	, db(Database::getInstance())
{
}

AppModel::~AppModel()
{
	Release();
}

void AppModel::_initialize()
{
	InitializationResult r;
	bool error = false;

	if (!loadConfigFile()) {
		r = ConfigRequired;
		error = true;

		cfg.host.clear();
		cfg.port = 0;
		cfg.schema.clear();
		cfg.user.clear();
		cfg.password.clear();

		wxLogError("[AppModell::initialize] configuration required");
	}
	else {
		std::string _port = getConfig("port");

		cfg.host = getConfig("host");
		cfg.port = _port.empty() ? 0 : std::stoi(_port);
		cfg.schema = getConfig("database");
		cfg.user = getConfig("user");
		cfg.password = getConfig("password");
	}

	if (!error && !db.connect()) {
		r = DatabaseError;
		error = true;

		wxLogError("[AppModell::initialize] configuration required");
	}
	else {
		UpdateValues();
	}

	if(!error) {
		r = OK;
	}

	wxLogMessage("[AppModell::initialize] success");

	// std::this_thread::sleep_for(std::chrono::milliseconds(500));

	wxCommandEvent evt(EVT_APPMODEL_INITIALIZED);
	evt.SetInt(r);
	evt.SetEventObject(this);
	wxQueueEvent(this, evt.Clone());
}
