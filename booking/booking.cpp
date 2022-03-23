#include <iomanip>
#include <iostream>
#include <map>
#include <deque>
#include <algorithm>
#include "../test_runner.h"

using namespace std;

struct Order {
    long long time;
    string hotelName;
    long clientId;
    int roomCount;
};

class Booking {
public:
    void book(long long time, const string &hotelName, long clientId, int roomCount) {
        auto upBound = upper_bound(orders.begin(), orders.end(), time - 86400, [](long long time, const Order &order) {
            return time < order.time;
        });
        auto it = orders.begin();
        while (it != upBound) {
            map<long, long>& clients = hotelToUniqueClients[it->hotelName];
            long& rooms = clients[it->clientId];
            rooms -= it->roomCount;
            if (rooms <= 0) {
                clients.erase(it->clientId);
            }
            hotelToRooms[it->hotelName] -= it->roomCount;
            it++;
            orders.pop_front();
        }

        orders.push_back({time, hotelName, clientId, roomCount});
        hotelToUniqueClients[hotelName][clientId] += roomCount;
        hotelToRooms[hotelName] += roomCount;
    }

    size_t clients(const string &hotelName) {
        return hotelToUniqueClients[hotelName].size();
    }

    int rooms(const string &hotelName) {
        return hotelToRooms[hotelName];
    }

private:
    deque<Order> orders;
    map<string, map<long, long>> hotelToUniqueClients;
    map<string, long> hotelToRooms;
};

void testAll() {
    {
        Booking booking;
        booking.book(1, "ABC hotel", 1, 1);
        booking.book(2, "ABC hotel", 1, 1);
        booking.book(3, "ABC hotel", 1, 1);

        ASSERT_EQUAL(booking.rooms("ABC hotel"), 3);
        ASSERT_EQUAL(booking.clients("ABC hotel"), 1);
        ASSERT_EQUAL(booking.rooms(""), 0);
        ASSERT_EQUAL(booking.clients("zxc"), 0);
    }
    {
        Booking booking;
        booking.book(1, "ABC hotel", 1, 1);
        booking.book(2, "ABC hotel", 1, 1);
        booking.book(100500, "ABC hotel", 1, 2);
        booking.book(2005000000, "ABCD hotel", 100000000, 200);

        ASSERT_EQUAL(booking.rooms("ABC hotel"), 0);
        ASSERT_EQUAL(booking.clients("ABC hotel"), 0);

        ASSERT_EQUAL(booking.rooms("ABCD hotel"), 200);
        ASSERT_EQUAL(booking.clients("ABCD hotel"), 1);
    }
}


int main() {
    // Для ускорения чтения данных отключается синхронизация
    // cin и cout с stdio,
    // а также выполняется отвязка cin от cout
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    TestRunner tr;
    RUN_TEST(tr, testAll);

    Booking booking;

    long query_count;
    cin >> query_count;

    for (long query_id = 0; query_id < query_count; ++query_id) {
        string cmd;
        cin >> cmd;
        if (cmd == "BOOK") {
            long long time;
            long clientId;
            int roomCount;
            string hotelName;
            cin >> time >> hotelName >> clientId >> roomCount;
            booking.book(time, hotelName, clientId, roomCount);
        } else {
            string hotelName;
            cin >> hotelName;
            if (cmd == "CLIENTS") {
                cout << booking.clients(hotelName) << endl;
            } else {
                cout << booking.rooms(hotelName) << endl;
            }
        }
    }

    return 0;
}