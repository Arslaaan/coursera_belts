#pragma once

#include "http_request.h"

#include <string_view>
#include <map>
#include <string>
#include <sstream>
#include <set>

using namespace std;

class Stats {
public:
    Stats();

    void AddMethod(string_view method);

    void AddUri(string_view uri);

    [[nodiscard]] const map<string_view, int> &GetMethodStats() const;

    [[nodiscard]] const map<string_view, int> &GetUriStats() const;

private:
    map<string_view, int> methodStats;
    map<string_view, int> uriStats;
    set<string_view> acceptableMethods = {"GET", "POST", "PUT", "DELETE"};
    set<string_view> acceptableUri = {"/", "/order", "/product", "/basket", "/help"};
    string_view UNKNOWN_METHOD = "UNKNOWN";
    string_view UNKNOWN_URI = "unknown";
};

HttpRequest ParseRequest(string_view line);
