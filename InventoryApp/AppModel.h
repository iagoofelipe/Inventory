#pragma once

#include "consts.h"
#include "Database.h"
#include "tools.h"

#include <wx/event.h>
#include <vector>
#include <fstream>

wxDECLARE_EVENT(EVT_APPMODEL_INITIALIZED, wxCommandEvent);
wxDECLARE_EVENT(EVT_APPMODEL_REGS_UPDATED, wxCommandEvent);
wxDECLARE_EVENT(EVT_APPMODEL_PRODUCTS_UPDATED, wxCommandEvent);

namespace inventory
{
	class AppModel : public wxEvtHandler
	{
	public:
		enum InitializationResult
		{
			ConfigRequired, InvalidConfig, DatabaseError, OK
		};

		AppModel(const AppModel&) = delete;
		AppModel& operator=(const AppModel&) = delete;

		void Initialize();
		void UpdateValues();
		const std::vector<Registry>& GetRegistries();
		const std::vector<Product>& GetProducts();
		const Registry& GetRegistryById(int id);
		const Product& GetProductById(int id);
		void SetDatabaseConnParams(const DatabaseConnParams& params);
		const DatabaseConnParams& GetDatabaseConnParams();
		static AppModel& GetInstance();

	private:
		AppModel();
		~AppModel();

		void _initialize();
		void dispatchInitialized(InitializationResult r);

		bool dbParamsSet;
		Database& db;
		Config& cfg;

		std::vector<Registry> regs;
		std::vector<Product> products;
		std::map<int, Registry*> regsById;
		std::map<int, Product*> productsById;
		DatabaseConnParams dbParams;
	};
}