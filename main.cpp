#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

using namespace std;

enum class QueryType {
    NewBus,
    BusesForStop,
    StopsForBus,
    AllBuses
};

struct Query {
    QueryType type;
    string bus;
    string stop;
    vector<string> stops;
};

istream& operator >> (istream& is, Query& q) {
    // Реализуйте эту функцию
    string operation_code;
    is >> operation_code;
    if (operation_code == "NEW_BUS") {
        q.type = QueryType::NewBus;
        is >> q.bus;

        int stop_count;
        is >> stop_count;
        q.stops.resize(stop_count);
        for (int i = 0; i < stop_count; ++i) {
            is >> q.stops[i];
        }
    } else if (operation_code == "BUSES_FOR_STOP") {
        q.type = QueryType::BusesForStop;
        is >> q.stop;
    } else if (operation_code == "STOPS_FOR_BUS") {
        q.type = QueryType::StopsForBus;
        is >> q.bus;
    } else if (operation_code == "ALL_BUSES") {
        q.type = QueryType::AllBuses;
    }
    return is;
}

struct BusesForStopResponse {
    // Наполните полями эту структуру
    vector<string> buses;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
    // Реализуйте эту функцию
    if (r.buses.empty()) {
        os << "No stop";
    } else {
        for (const string& bus : r.buses) {
            os << bus << " ";
        }
    }
    return os;
}

struct StopsForBusResponse {
    // Наполните полями эту структуру
    string bus;
    vector<string> stops;
    map<string, vector<string>> busesForStop; // stop -> bus1, bus2 ...
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
    // Реализуйте эту функцию
    if (r.bus.empty()) {
        os << "No bus";
    } else {
        for (const string& stop : r.stops) {
            os << "Stop " << stop << ": ";
            if (r.busesForStop.at(stop).size() == 1) {
                os << "no interchange" << endl;
            } else {
                for (const string& other_bus : r.busesForStop.at(stop)) {
                    if (r.bus != other_bus) {
                        os << other_bus << " ";
                    }
                }
                os << endl;
            }
        }
    }
    return os;
}

struct AllBusesResponse {
    // Наполните полями эту структуру
    vector<StopsForBusResponse> stopsForBuses;
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
    // Реализуйте эту функцию
    if (r.stopsForBuses.empty()) {
        os << "No buses";
    } else {
        for (const auto& stops_for_bus : r.stopsForBuses) {
            os << "Bus " << stops_for_bus.bus << ": ";
            for (const string& stop : stops_for_bus.stops) {
                os << stop << " ";
            }
            os << endl; // todo тут возможно лишний эндл
        }
    }
    return os;
}

class BusManager {
    map<string, vector<string>> stopsForBus;
    map<string, vector<string>> busesForStop;
public:
    void AddBus(const string& bus, const vector<string>& stops) {
        // Реализуйте этот метод
        stopsForBus.insert({bus, stops});
        for (const string& stop: stops) {
            busesForStop[stop].push_back(bus);
        }
    }

    BusesForStopResponse GetBusesForStop(const string& stop) const {
        // Реализуйте этот метод
        if (busesForStop.count(stop) == 0) {return {};}
        return {busesForStop.at(stop)};
    }

    StopsForBusResponse GetStopsForBus(const string& bus) const {
        // Реализуйте этот метод
        if (stopsForBus.count(bus) == 0) {return {};}
        return {bus, stopsForBus.at(bus), busesForStop};
    }

    AllBusesResponse GetAllBuses() const {
        // Реализуйте этот метод
        vector<StopsForBusResponse> stopsForBusResponse;
        for(const auto& stopForBus: stopsForBus) {
            stopsForBusResponse.push_back({stopForBus.first, stopForBus.second});
        }
        return {stopsForBusResponse};
    }
};

// Не меняя тела функции main, реализуйте функции и классы выше

int main() {
    int query_count;
    Query q;

    cin >> query_count;

    BusManager bm;
    for (int i = 0; i < query_count; ++i) {
        cin >> q;
        switch (q.type) {
            case QueryType::NewBus:
                bm.AddBus(q.bus, q.stops);
                break;
            case QueryType::BusesForStop:
                cout << bm.GetBusesForStop(q.stop) << endl;
                break;
            case QueryType::StopsForBus:
                cout << bm.GetStopsForBus(q.bus) << endl;
                break;
            case QueryType::AllBuses:
                cout << bm.GetAllBuses() << endl;
                break;
        }
    }

    return 0;
}
