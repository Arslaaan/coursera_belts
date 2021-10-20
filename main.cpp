#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <iomanip>

using namespace std;

struct Date {
    Date(int day, int month, int year) {
        this->day = day;
        this->month = month;
        this->year = year;
    }

    int day;
    int month;
    int year;
};

ostream &operator<<(ostream &out, const Date &date) {
    out << setw(4) << setfill('0') << date.year << "-";
    out << setw(2) << setfill('0') << date.month << "-";
    out << setw(2) << setfill('0') << date.day;
    return out;
}

class History {
    map<Date, set<string>> events;

public:
    void add(const Date &date, const string &s) {
        events[date].insert(s);
    }

    void del(const Date &date, const string &s) {
        if (events.count(date) > 0) {
            set<string> &current_events = events[date];
            if (current_events.count(s) > 0) {
                current_events.erase(s);
                cout << "Deleted successfully" << endl;
                return;
            }
        }
        cout << "Event not found" << endl;
    }

    void del(const Date &date) {
        if (events.count(date) > 0) {
            set<string> &current_events = events[date];
            if (!current_events.empty()) {
                cout << "Deleted " << current_events.size() << " events" << endl;
                current_events.clear();
                return;
            }
        }
        cout << "Deleted 0 events" << endl;
    }

    void find(const Date &date) {
        for (const auto &e: events[date]) {
            cout << e << endl;
        }
    }

    void print() {
        for (const auto &event : events) {
            for (const auto &set_elem: event.second) {
                cout << event.first << " " << set_elem << endl;
            }
        }
    }
};

void checkDate(const Date &date) {
    if (date.month >= 1 && date.month <= 12) {
        if (date.day >= 1 && date.day <= 31) {
            //nothing
        } else {
            cout << "Day value is invalid: " << date.day << endl;
            throw runtime_error("");
        }
    } else {
        cout << "Month value is invalid: " << date.month << endl;
        throw runtime_error("");
    }
}

istream &operator>>(istream &in, Date &date) {
    string full;
    in >> full;
    stringstream ss(full);

    int y, m, d;
    char def1, def2;
    ss >> y >> def1 >> m >> def2 >> d;
    if (ss && def1 == '-' && def2 == '-' && d >= 0 && m >= 0 && y >= 0 && ss.eof()) {
        date = Date(d, m, y);
        checkDate(date);
    } else {
        cout << "Wrong date format: " << full << endl;
        throw runtime_error("");
    }
    return in;
}

bool operator<(const Date &date1, const Date &date2) {
    if (date1.year == date2.year) {
        if (date1.month == date2.month) {
            return date1.day < date2.day;
        } else {
            return date1.month < date2.month;
        }
    } else {
        return date1.year < date2.year;
    }
}

bool operator==(const Date &date1, const Date &date2) {
    return date1.year == date2.year && date1.month == date2.month && date1.day == date2.day;
}

int main() {
    History history;
    string line;

    while (getline(cin, line)) {
        try {
            string cmd, event;
            stringstream lineStream = stringstream(line);
            Date date(0, 0, 0);
            lineStream >> cmd;
            if (cmd == "Add") {
                lineStream >> date >> event;
                history.add(date, event);
            } else if (cmd == "Del") {
                lineStream >> date;
                if (lineStream && !lineStream.eof()) {
                    lineStream >> event;
                    history.del(date, event);
                } else {
                    history.del(date);
                }
            } else if (cmd == "Find") {
                lineStream >> date;
                history.find(date);
            } else if (cmd == "Print") {
                history.print();
            } else if (!cmd.empty()) {
                cout << "Unknown command: " << cmd << endl;
            }

        }
        catch (exception &ex) {

        }
    }
    return 0;
}