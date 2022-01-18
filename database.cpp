#include "database.h"

void Database::Add(const Date &date, const std::string &event) {
    Record record(date, event);
    if (records_set.insert(record).second) {
        records_map[date].push_back(record);
    }
}

void Database::Print(std::ostream &ostream) const {
    for (const auto &entry: records_map) {
        for (const auto &record: entry.second) {
            ostream << record << endl;
        }
    }
}

int Database::RemoveIf(const std::function<bool(Date, string)> &condition) {
    size_t counter = 0;
    for (auto record_map_it = records_map.begin(); record_map_it != records_map.end();) {
        vector<Record>& records_for_date = record_map_it->second;
        auto it_begin_false_condition = stable_partition(records_for_date.begin(), records_for_date.end(), [condition](const Record& r) {
            return !condition(r.getDate(), r.getEvent());
        });
        for (auto it = it_begin_false_condition; it != records_for_date.end();it++) {
            records_set.erase(*it);
            counter++;
        }
        if (distance(it_begin_false_condition, records_for_date.end()) == records_for_date.size()) {
            record_map_it = records_map.erase(record_map_it);
        } else {
            records_for_date.erase(it_begin_false_condition, records_for_date.end());
            record_map_it++;
        }
    }
    return counter;
}

vector<Record>
Database::FindIf(const std::function<bool(Date, string)> &condition) const {
    vector<Record> result;
    for (const auto & record_map_it : records_map) {
        for (const auto& record: record_map_it.second) {
            if (condition(record.getDate(), record.getEvent())) {
                result.emplace_back(record.getDate(), record.getEvent());
            }
        }
    }
    return result;
}

const Record &Database::Last(const Date &date) const {
    const auto &up_bound = upper_bound(records_map.begin(), records_map.end(), date,
                                       [](const Date &date_, const pair<Date, vector<Record>> &pair_) {
                                           return date_ < pair_.first;
                                       });
    if (up_bound == records_map.begin()) {
        throw invalid_argument("no elements before");
    }
    const auto &last = prev(up_bound);
    return last->second.back();
}

ostream &operator<<(ostream &out, const pair<Date, string> &entity) {
    out << entity.first << " " << entity.second;
    return out;
}

Record::Record(const Date &date, string event) : date(date), event(std::move(event)) {}

const Date &Record::getDate() const {
    return date;
}

const string &Record::getEvent() const {
    return event;
}

bool Record::operator==(const Record &another_record) const {
    return date == another_record.getDate() && event == another_record.getEvent();
}

bool Record::operator<(const Record &another_record) const {
    if (date == another_record.getDate()) {
        return event < another_record.getEvent();
    } else {
        return date < another_record.getDate();
    }
}

bool Record::operator!=(const Record &another_record) const {
    return !(*this == another_record);
}

ostream &operator<<(ostream &out, const Record &record) {
    out << record.getDate() << " " << record.getEvent();
    return out;
}
