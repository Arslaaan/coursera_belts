#include "database.h"

void Database::Add(const Date &date, const std::string &event) {
    vector<string> &events_ = events[date];
    for (const string &e: events_) {
        if (e == event) {
            return;
        }
    }
    events_.push_back(event);
}

void Database::Print(std::ostream &ostream) const {
    for (const auto &entry: events) {
        for (const auto &date_event: entry.second) {
            ostream << make_pair<const Date &, const string &>(entry.first, date_event) << endl;
        }
    }
}

int Database::RemoveIf(const std::function<bool(Date, string)>& condition) {
    size_t counter = 0;
    for (auto entry = events.begin(); entry != events.end();) {
        vector<string> &date_events = entry->second;
        size_t size_before = date_events.size();
        date_events.erase(remove_if(date_events.begin(), date_events.end(), [entry, condition](const string &event) {
            return condition(entry->first, event);
        }), date_events.end());

        size_t diff = size_before - date_events.size();
        counter += diff;

        if (date_events.empty()) {
            entry = events.erase(entry); // todo будет работать ?
        } else {
            ++entry;
        }
    }
    return counter;
}

vector<pair<Date, string>>
Database::FindIf(const std::function<bool(Date, string)>& condition) const {
    vector<pair<Date, string>> result;
    for (auto &entry: events) {
        for (const auto &date_event: entry.second) {
            if (condition(entry.first, date_event)) {
                result.emplace_back(entry.first, date_event);
            }
        }
    }
    return result;
}

string Database::Last(const Date &date) const {
    const auto &up_bound = upper_bound(events.begin(), events.end(), date,
                                       [](const Date &date_, const pair<Date, vector<string>> &pair_) {
                                           return date_ < pair_.first;
                                       });
    if (up_bound == events.begin()) {
        throw invalid_argument("no elements before");
    }
    const auto &last = prev(up_bound);
    stringstream ss;
    ss << make_pair<>(last->first, last->second.back());
    return ss.str();
}

ostream &operator<<(ostream &out, const pair<Date, string>& entity) {
    out << entity.first << " " << entity.second;
    return out;
}
