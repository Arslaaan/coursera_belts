#pragma once

#include <string>
#include <memory>
#include <functional>
#include <map>
#include <set>

#include "node.h"

class Database {
    map<Date, vector<string>> events;
public:
    void Add(const Date &date, const std::string &event);

    void Print(std::ostream &ostream) const;

    string Last(const Date &date) const;

    vector<pair<Date, string>> FindIf(const std::function<bool(Date, string)>& condition) const;

    int RemoveIf(const std::function<bool(Date, string)>& condition);
};

ostream& operator<<(ostream& out, const pair<Date, string>& entity);
