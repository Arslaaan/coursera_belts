#pragma once

#include <string>
#include <memory>
#include <functional>
#include <map>
#include <set>
#include <list>

#include "node.h"

class Record {
private:
    Date date;
    string event;
public:
    Record(const Date &date, string event);

    const Date &getDate() const;

    const string &getEvent() const;

    bool operator==(const Record &another_record) const;

    bool operator!=(const Record &another_record) const;

    bool operator<(const Record &another_record) const;
};

class Database {
    set<Record> records_set;
    map<Date, vector<Record>> records_map;
public:
    void Add(const Date &date, const std::string &event);

    void Print(std::ostream &ostream) const;

    const Record &Last(const Date &date) const;

    vector<Record> FindIf(const std::function<bool(Date, string)> &condition) const;

    int RemoveIf(const std::function<bool(Date, string)> &condition);
};

ostream& operator<<(ostream &out, const Record& record);
