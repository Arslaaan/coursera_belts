#include "bus_manager.h"

void BusManager::AddBus(const string& bus, const vector<string>& stops) {
    // Реализуйте этот метод
    stopsForBus.insert({bus, stops});
    for (const string& stop: stops) {
        busesForStop[stop].push_back(bus);
    }
}

BusesForStopResponse BusManager::GetBusesForStop(const string& stop) const {
    // Реализуйте этот метод
    if (busesForStop.count(stop) == 0) {return {};}
    return {busesForStop.at(stop)};
}

StopsForBusResponse BusManager::GetStopsForBus(const string& bus) const {
    // Реализуйте этот метод
    if (stopsForBus.count(bus) == 0) {return {};}
    return {bus, stopsForBus.at(bus), busesForStop};
}

AllBusesResponse BusManager::GetAllBuses() const {
    // Реализуйте этот метод
    vector<StopsForBusResponse> stopsForBusResponse;
    for(const auto& stopForBus: stopsForBus) {
        stopsForBusResponse.push_back({stopForBus.first, stopForBus.second});
    }
    return {stopsForBusResponse};
}