#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <set>

using namespace std;

class RouteManager {
public:
    void AddRoute(int start, int finish) {
        stations[start].insert(finish);
        stations[finish].insert(start);
    }

    int FindNearestFinish(int start, int finish) const {
        if (stations.count(start) == 0) {
            return abs(start - finish);
        }
        const auto &reachableStations = stations.at(start);

        auto rightStation = reachableStations.lower_bound(finish);
        if (rightStation == reachableStations.end()) {
            rightStation = prev(rightStation);
        }
        auto leftStation = rightStation;
        if (rightStation != reachableStations.begin()) {
            leftStation = prev(rightStation);
        }
        return min(min(abs(finish - *leftStation), abs(finish - *rightStation)), abs(start - finish));
    }

private:
    map<int, set<int>> stations;
};


int main() {
    RouteManager routes;

    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        cin >> query_type;
        int start, finish;
        cin >> start >> finish;
        if (query_type == "ADD") {
            routes.AddRoute(start, finish);
        } else if (query_type == "GO") {
            cout << routes.FindNearestFinish(start, finish) << "\n";
        }
    }

    return 0;
}
