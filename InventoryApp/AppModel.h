#pragma once

#include "consts.h"
#include "Database.h"

#include <wx/event.h>
#include <vector>
#include <fstream>

wxDECLARE_EVENT(EVT_APPMODEL_INITIALIZED, wxCommandEvent);
wxDECLARE_EVENT(EVT_APPMODEL_REGS_UPDATED, wxCommandEvent);
wxDECLARE_EVENT(EVT_APPMODEL_PRODUCTS_UPDATED, wxCommandEvent);

class AppModel : public wxEvtHandler
{
public:
	enum InitializationResult
	{
		ConfigRequired, DatabaseError, OK
	};

	AppModel(const AppModel&) = delete;
	AppModel& operator=(const AppModel&) = delete;

	void Initialize();
	void UpdateValues();
	const std::vector<Registry>& GetRegistries();
	const std::vector<Product>& GetProducts();
	const Registry& GetRegistryById(int id);
	const Product& GetProductById(int id);

	static AppModel& getInstance();
	static void DeleteLater(ConfigParams* obj);
	static void Release();
	static ConfigParams GetConfig();
	static void SetConfig(const ConfigParams& cfg);

private:
	AppModel();
	~AppModel();

	void _initialize();

	static bool cleaned;
	static std::vector<ConfigParams*> toDelete_ConfigParams;
	static ConfigParams cfg;
	static std::ofstream* logFile;

	Database& db;
	std::vector<Registry> regs;
	std::vector<Product> products;
	std::map<int, Registry*> regsById;
	std::map<int, Product*> productsById;
};