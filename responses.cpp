#include "responses.h"

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