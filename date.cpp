#include "date.h"

Date::Date() : year(0), month(0), day(0) {}

int Date::getYear() const {
    return year;
}

int Date::getMonth() const {
    return month;
}

int Date::getDay() const {
    return day;
}

Date::Date(int y, int m, int d) : year(y), month(m), day(d) {};

std::ostream& operator<<(std::ostream& out, const Date& date) {
    out << std::setw(4) << std::setfill('0') << date.getYear();
    out << "-";
    out << std::setw(2) << std::setfill('0') << date.getMonth();
    out << "-";
    out << std::setw(2) << std::setfill('0') << date.getDay();
    return out;
}

Date ParseDate(std::istream &input) {
    int year, month, day;
    char divider;
    input >> year >> divider >> month >> divider >> day;
    return Date(year, month, day);
}

