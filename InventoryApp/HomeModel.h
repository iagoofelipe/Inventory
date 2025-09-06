#pragma once

#include "Database.h"
#include "AppModel.h"

namespace inventory
{
	class HomeModel
	{
	public:
		HomeModel();

		void GetIntervalProperties(int* start, int* end, int* total);
		wxString GetLabel();
		const std::vector<Registry*>* GetValue();
		const std::vector<Registry*>* Next();
		const std::vector<Registry*>* Previous();
		bool HasNext() const;
		bool HasPrevious() const;
		void SetDateRange(const wxDateTime& start, const wxDateTime& end);
		int SetCurrentInterval(int index);
		int GetCurrentInterval();
		int Count();
		void UpdateValues();

	private:
		AppModel& appModel;
		Database& db;
		std::vector<Registry> regs;
		std::vector<std::vector<Registry*>> regsByInterval;
		std::vector<Registry*>* pInterval;
		std::string dtStart;
		std::string dtEnd;
		int maxInterval, numItems, numIntervals, indexInterval;
	};
}

