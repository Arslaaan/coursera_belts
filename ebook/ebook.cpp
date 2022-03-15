#include <iomanip>
#include <iostream>
#include <vector>
#include <set>
#include <map>

using namespace std;

class ReadingManager {
public:
    ReadingManager() {};

    void Read(int user_id, int page_count) {
        auto currentPage = userToPage.find(user_id);
        if (currentPage != userToPage.end()) {
            auto &usersForPrevPage = pageToUsers[currentPage->second];
            usersForPrevPage.erase(currentPage->first);
            if (usersForPrevPage.empty()) {
                pageToUsers.erase(currentPage->second);
            }
        } else {
            allUsers++;
        }
        userToPage[user_id] = page_count;
        pageToUsers[page_count].insert(user_id);
    }

    double Cheer(int user_id) const {
        auto userPageIter = userToPage.find(user_id);
        if (userPageIter == userToPage.end()) {
            return 0;
        }
        auto endIterForCurrent = pageToUsers.lower_bound(userPageIter->second);
        int lessReadingUsers = 0;
        for(auto it = pageToUsers.begin(); it != endIterForCurrent;++it) {
            lessReadingUsers += it->second.size();
        }
        if (lessReadingUsers == allUsers - 1) {
            return 1;
        }
        return lessReadingUsers * 1.0 / (allUsers - 1);
    }

private:
    map<int, set<int>> pageToUsers;
    map<int, int> userToPage;

    int allUsers = 0;
};


int main() {
    // Для ускорения чтения данных отключается синхронизация
    // cin и cout с stdio,
    // а также выполняется отвязка cin от cout
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ReadingManager manager;

    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        cin >> query_type;
        int user_id;
        cin >> user_id;

        if (query_type == "READ") {
            int page_count;
            cin >> page_count;
            manager.Read(user_id, page_count);
        } else if (query_type == "CHEER") {
            cout << setprecision(6) << manager.Cheer(user_id) << "\n";
        }
    }

    return 0;
}