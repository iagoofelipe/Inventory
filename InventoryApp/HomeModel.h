#pragma once

#include "Database.h"
#include "AppModel.h"

namespace inventory
{
	class HomeModel
	{
	public:
		HomeModel();

		const std::vector<Registry*>* GetRegistries(const wxDateTime& start, const wxDateTime& end, int interval = 0);
		int GetNumIntervals() const;

	private:
		AppModel& appModel;
		Database& db;
		std::vector<Registry> regs;
		std::vector<std::vector<Registry*>> regsByInterval;
		std::string dtStart;
		std::string dtEnd;
		int maxInterval, numIntervals;
	};
}

