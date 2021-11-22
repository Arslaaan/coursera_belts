//
// Created by aochi on 10.11.2021.
//

#ifndef COURSERA_BUS_MANAGER_H
#define COURSERA_BUS_MANAGER_H

#include <string>
#include <vector>
#include <map>

#include "responses.h"

using namespace std;

class BusManager {
    map<string, vector<string>> stopsForBus;
    map<string, vector<string>> busesForStop;
public:
    void AddBus(const string& bus, const vector<string>& stops);

    BusesForStopResponse GetBusesForStop(const string& stop) const;

    StopsForBusResponse GetStopsForBus(const string& bus) const;

    AllBusesResponse GetAllBuses() const;
};


#endif //COURSERA_BUS_MANAGER_H
