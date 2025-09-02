#include "HomeModel.h"

namespace inventory
{
    HomeModel::HomeModel()
        : appModel(AppModel::GetInstance())
        , db(Database::GetInstance())
        , maxInterval(MAX_LEN_TAB_PRODUCTS)
        , numIntervals(0)
    {
    }

    const std::vector<Registry*>* HomeModel::GetRegistries(const wxDateTime& start, const wxDateTime& end, int interval)
    {
        std::string
            s = start.Format("%Y-%m-%d %H:%M:%S").ToStdString(),
            e = end.Format("%Y-%m-%d %H:%M:%S").ToStdString();

        // getting data
        if (dtStart != s || dtEnd != e) {
            dtStart = s;
            dtEnd = e;

            regs.clear();
            regsByInterval.clear();
            db.getRegistriesByRange(regs, dtStart, dtEnd);

            // whether is no data
            size_t size = regs.size();
            if (!size) {
                numIntervals = 0;
                return nullptr;
            }

            // split the data to a navigable view by index
            numIntervals = size / maxInterval + bool(size % maxInterval);

            // create the sections
            for (int i = 0; i < numIntervals; i++) {
                regsByInterval.emplace_back();
                regsByInterval[i].reserve(maxInterval);
            }
            
            // setting data into the sections
            for (int i = 0, count = 0, interval = 0; i < size; i++) {
                regsByInterval[interval].emplace_back(&regs[i]);

                if (++count == maxInterval) {
                    interval++;
                    count = 0;
                }
            }
        }

        return &regsByInterval[(interval >= 0 && interval < regsByInterval.size()) ? interval : 0];
    }

    int HomeModel::GetNumIntervals() const
    {
        return numIntervals;
    }
}
