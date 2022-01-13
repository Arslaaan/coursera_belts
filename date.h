#pragma once

#include <iostream>
#include <sstream>
#include <iomanip>

class Date {
    int year;
    int month;
    int day;
public:
    Date();
    Date(int y, int m, int d);
    int getYear() const;
    int getMonth() const;
    int getDay() const;
    bool operator<(const Date& another_date) const {
        return std::make_tuple(year, month, day) < std::make_tuple(another_date.year, another_date.month, another_date.day);
    }
    bool operator==(const Date& another_date) const {
        return std::make_tuple(year, month, day) == std::make_tuple(another_date.year, another_date.month, another_date.day);
    }
    bool operator>(const Date& another_date) const {
        return std::make_tuple(year, month, day) > std::make_tuple(another_date.year, another_date.month, another_date.day);
    }
};

std::ostream& operator<<(std::ostream& out, const Date& date);

Date ParseDate(std::istream &input);