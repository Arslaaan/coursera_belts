#include "database.h"

void Database::Add(const Date &date, const std::string &event) {
    Record record(date, event);
    if (!records_set.count(record)) {
        std::set<Record>::key_compare comp = records_set.key_comp();
        bool x = comp(record, Record({2020, 1, 15}, "Katya"));
        bool y = comp(Record({2020, 1, 15}, "Katya"), record);
        records_set.insert(record);
        records_map[date].push_back(record);
    }
}

void Database::Print(std::ostream &ostream) const {
//    ostream << "Print map" << endl;
    for (const auto &entry: records_map) {
        for (const auto &record: entry.second) {
            ostream << record << endl;
        }
    }
//    ostream << "Print set" << endl;
//    for (const auto& e: records_set) {
//        ostream << e << endl;
//    }
}

int Database::RemoveIf(const std::function<bool(Date, string)> &condition) {
    size_t counter = 0;
    for (auto record_it = records_set.begin(); record_it != records_set.end();) {
        const Record& record = *record_it;
        if (condition(record.getDate(), record.getEvent())) {
            counter++;
            list<Record> &list_for_date = records_map[record.getDate()];
            for (auto list_it = list_for_date.begin(); list_it != list_for_date.end();) {
                if (*list_it == record) {
                    list_it = list_for_date.erase(list_it);
                    break;
                } else {
                    list_it++;
                }
            }
            if (list_for_date.empty()) {
                records_map.erase(record.getDate());
            }
            record_it = records_set.erase(record_it);
        } else {
            record_it++;
        }
    }
    return counter;
}

vector<Record>
Database::FindIf(const std::function<bool(Date, string)> &condition) const {
    vector<Record> result;
    for (auto record_it = records_set.begin(); record_it != records_set.end();) {
        const Record& record = *record_it;
        if (condition(record.getDate(), record.getEvent())) {
            result.emplace_back(record.getDate(), record.getEvent());
        }
        record_it++;
    }
    return result;
}

const Record &Database::Last(const Date &date) const {
    const auto &up_bound = upper_bound(records_map.begin(), records_map.end(), date,
                                       [](const Date &date_, const pair<Date, list<Record>> &pair_) {
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

Record::Record(const Date &date, const string &event) : date(date), event(event) {}

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

//bool Record::operator>(const Record &another_record) const {
//    return date > another_record.getDate();
//}

bool Record::operator!=(const Record &another_record) const {
    return !(*this == another_record);
}

ostream &operator<<(ostream &out, const Record &record) {
    out << record.getDate() << " " << record.getEvent();
    return out;
}
