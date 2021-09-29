#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

// если имя неизвестно, возвращает пустую строку
string FindNameByYear(const map<int, string> &names, int year) {
    string name;  // изначально имя неизвестно

    // перебираем всю историю по возрастанию ключа словаря, то есть в хронологическом порядке
    for (const auto &item : names) {
        // если очередной год не больше данного, обновляем имя
        if (item.first <= year) {
            name = item.second;
        } else {
            // иначе пора остановиться, так как эта запись и все последующие относятся к будущему
            break;
        }
    }

    return name;
}

vector<string> FindPrevNamesByYear(const map<int, string> &names, int year) {
    vector<string> prevNames;
    string prevPrevName;
    // перебираем всю историю по возрастанию ключа словаря, то есть в хронологическом порядке
    for (const auto &item : names) {
        // если очередной год не больше данного, обновляем имя
        if (item.first <= year) {
            if (prevPrevName != item.second) {
                prevNames.push_back(item.second);
            }
            prevPrevName = item.second;
        } else {
            // иначе пора остановиться, так как эта запись и все последующие относятся к будущему
            break;
        }
    }

    reverse(begin(prevNames), end(prevNames));
    return prevNames;
}

string adaptHistory(const vector<string> &names) {
    string historyOfNames = " (";
    if (names.size() > 1) {
        for (int i = 1; i < names.size(); ++i) {
            historyOfNames += names[i] + ", ";
        }
        historyOfNames.erase(historyOfNames.size() - 2, historyOfNames.size() - 1);
        historyOfNames += ")";
        return historyOfNames;
    }
    return "";
}

class Person {
public:
    Person(const string &s1, const string &s2, int y) {
        first_names[y] = s1;
        last_names[y] = s2;
        birthday = y;
    }

    void ChangeFirstName(int year, const string &first_name) {
        if (year >= birthday) {
            first_names[year] = first_name;
        }
    }

    void ChangeLastName(int year, const string &last_name) {
        if (year >= birthday) {
            last_names[year] = last_name;
        }
    }

    string GetFullName(int year) const {
        if (year < birthday) {
            return "No person";
        }
        // получаем имя и фамилию по состоянию на год year
        const string first_name = FindNameByYear(first_names, year);
        const string last_name = FindNameByYear(last_names, year);

        // если и имя, и фамилия неизвестны
        if (first_name.empty() && last_name.empty()) {
            return "Incognito";

            // если неизвестно только имя
        } else if (first_name.empty()) {
            return last_name + " with unknown first name";

            // если неизвестна только фамилия
        } else if (last_name.empty()) {
            return first_name + " with unknown last name";

            // если известны и имя, и фамилия
        } else {
            return first_name + " " + last_name;
        }
    }

    string GetFullNameWithHistory(int year) const {
        if (year < birthday) {
            return "No person";
        }
        // получить все имена и фамилии по состоянию на конец года year
        const string first_name = FindNameByYear(first_names, year);
        const string last_name = FindNameByYear(last_names, year);

        vector<string> prevNames = FindPrevNamesByYear(first_names, year);
        vector<string> prevLastNames = FindPrevNamesByYear(last_names, year);

        // если и имя, и фамилия неизвестны
        if (first_name.empty() && last_name.empty()) {
            return "Incognito";

            // если неизвестно только имя
        } else if (first_name.empty()) {
            return last_name + adaptHistory(prevLastNames) + " with unknown first name";

            // если неизвестна только фамилия
        } else if (last_name.empty()) {
            return first_name + adaptHistory(prevNames) + " with unknown last name";

            // если известны и имя, и фамилия
        } else {
            return first_name + adaptHistory(prevNames) + " " +
                   last_name + adaptHistory(prevLastNames);
        }
    }

private:
    map<int, string> first_names;
    map<int, string> last_names;
    int birthday;
};

int main() {
    Person person("Polina", "Sergeeva", 1960);
    for (int year : {1959, 1960}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeFirstName(1965, "Appolinaria");
    person.ChangeLastName(1967, "Ivanova");
    for (int year : {1965, 1967}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    return 0;
}