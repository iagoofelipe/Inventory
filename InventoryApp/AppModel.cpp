#include "AppModel.h"

#include <wx/wx.h>

#include <thread>
#include <chrono>

wxDEFINE_EVENT(EVT_APPMODEL_INITIALIZED, wxCommandEvent);
wxDEFINE_EVENT(EVT_APPMODEL_REGS_UPDATED, wxCommandEvent);
wxDEFINE_EVENT(EVT_APPMODEL_PRODUCTS_UPDATED, wxCommandEvent);

namespace inventory
{
	AppModel& AppModel::GetInstance()
	{
		static AppModel instance;
		return instance;
	}

	void AppModel::Initialize()
	{
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

	void AppModel::SetDatabaseConnParams(const DatabaseConnParams& params)
	{
		dbParams = params;
		dbParamsSet = true;

		cfg.Set("host", params.host);
		cfg.Set("port", std::to_string(params.port));
		cfg.Set("user", params.user);
		cfg.Set("password", params.password);
		cfg.Set("database", params.schema);

		cfg.UpdateFile();
	}

	const DatabaseConnParams& AppModel::GetDatabaseConnParams()
	{
		return dbParams;
	}

	AppModel::AppModel()
		: wxEvtHandler()
		, db(Database::GetInstance())
		, cfg(Config::GetInstance())
		, dbParamsSet(false)
	{
	}

	AppModel::~AppModel()
	{
	}

	void AppModel::_initialize()
	{
		// initialize config
		if (!cfg.Initialize()) {
			dbParamsSet = true;
			dbParams.host = DB_DEF_HOST;
			dbParams.user = DB_DEF_USER;
			dbParams.schema = DB_DEF_SCHEMA;
			dbParams.port = DB_DEF_PORT;
			dbParams.password = DB_DEF_PASSWORD;
			dispatchInitialized(InitializationResult::ConfigRequired);
			return;
		}

		// validate config
		if (!dbParamsSet) {
			dbParamsSet = true;
			dbParams.host = cfg["host"];
			dbParams.user = cfg["user"];
			dbParams.schema = cfg["database"];
			dbParams.port = cfg["port"].empty() ? 0 : std::stoi(cfg["port"]);
			dbParams.password = cfg["password"];
		}

		if (dbParams.host.empty() || dbParams.user.empty() || dbParams.schema.empty()) {
			dispatchInitialized(InitializationResult::InvalidConfig);
			return;
		}

		// try to connect with database
		if (!db.connect(dbParams)) {
			dispatchInitialized(InitializationResult::DatabaseError);
			return;
		}

		UpdateValues();
		dispatchInitialized(InitializationResult::OK);
	}

	void AppModel::dispatchInitialized(InitializationResult r)
	{
		wxCommandEvent evt(EVT_APPMODEL_INITIALIZED);
		
		switch (r)
		{
		case ConfigRequired:
			evt.SetString("Configuration no found");
			break;

		case InvalidConfig:
			evt.SetString("The configuration is not valid");
			break;

		case DatabaseError:
			evt.SetString("It was not possible to connect with database");
			break;
		}

		evt.SetInt(r);
		evt.SetEventObject(this);
		wxQueueEvent(this, evt.Clone());
	}
}