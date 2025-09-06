#include "HomeModel.h"

namespace inventory
{
    HomeModel::HomeModel()
        : appModel(AppModel::GetInstance())
        , db(Database::GetInstance())
        , pInterval(nullptr)
        , maxInterval(MAX_LEN_TAB_PRODUCTS)
        , numItems(0)
        , numIntervals(0)
        , indexInterval(-1)
    {
    }

    void HomeModel::GetIntervalProperties(int* start, int* end, int* total)
    {
        if (numItems) {
            *start = indexInterval * maxInterval + 1,
            *end = indexInterval == numIntervals - 1 ? numItems : (indexInterval + 1) * maxInterval;
        }
        else {
            *start = 0;
            *end = 0;
        }

        *total = numItems;
    }

    wxString HomeModel::GetLabel()
    {
        int start, end, total;
        GetIntervalProperties(&start, &end, &total);
        return wxString::Format("%u to %u of %u item(s)", start, end, total);
    }

    const std::vector<Registry*>* HomeModel::GetValue()
    {
        return numItems? pInterval : nullptr;
    }

    const std::vector<Registry*>* HomeModel::Next()
    {
        return HasNext() ? &regsByInterval[++indexInterval] : nullptr;
    }

    const std::vector<Registry*>* HomeModel::Previous()
    {
        return HasPrevious() ? &regsByInterval[--indexInterval] : nullptr;
    }

    bool HomeModel::HasNext() const
    {
        return indexInterval >= 0 && indexInterval < numIntervals - 1;
    }

    bool HomeModel::HasPrevious() const
    {
        return indexInterval > 0 && indexInterval < numIntervals;
    }

    void HomeModel::SetDateRange(const wxDateTime& start, const wxDateTime& end)
    {
        std::string
            s = start.Format("%Y-%m-%d %H:%M:%S").ToStdString(),
            e = end.Format("%Y-%m-%d %H:%M:%S").ToStdString();

        if (dtStart == s && dtEnd == e)
            return;

        dtStart = s; dtEnd = e;
        UpdateValues();
    }

    int HomeModel::SetCurrentInterval(int index)
    {
        if (!numItems) return -1;

        pInterval = &regsByInterval[(indexInterval = index > numIntervals ? 0 : index)];
        return indexInterval;
    }

    int HomeModel::GetCurrentInterval()
    {
        return indexInterval;
    }

    int HomeModel::Count()
    {
        return numItems;
    }

    void HomeModel::UpdateValues()
    {
        if (dtStart.empty() || dtEnd.empty()) return;

        regs.clear();
        regsByInterval.clear();
        db.getRegistriesByRange(regs, dtStart, dtEnd);

        numItems = regs.size();
        numIntervals = numItems / maxInterval + bool(numItems % maxInterval);

        if (!numItems) return;

        // create the sections
        for (int i = 0; i < numIntervals; i++) {
            regsByInterval.emplace_back();
            regsByInterval[i].reserve(maxInterval);
        }

        // setting data into the sections
        for (int i = 0, count = 0, interval = 0; i < numItems; i++) {
            regsByInterval[interval].emplace_back(&regs[i]);

            if (++count == maxInterval) {
                interval++;
                count = 0;
            }
        }

        // setting default interval
        SetCurrentInterval(0);
    }
}
