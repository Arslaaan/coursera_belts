#pragma once

#include <string>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

struct BusesForStopResponse {
    // Наполните полями эту структуру
    vector<string> buses;
};

struct StopsForBusResponse {
    // Наполните полями эту структуру
    string bus;
    vector<string> stops;
    map<string, vector<string>> busesForStop; // stop -> bus1, bus2 ...
};

struct AllBusesResponse {
    // Наполните полями эту структуру
    vector<StopsForBusResponse> stopsForBuses;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r);
ostream& operator << (ostream& os, const BusesForStopResponse& r);
ostream& operator << (ostream& os, const AllBusesResponse& r);