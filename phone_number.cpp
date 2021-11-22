//
// Created by aochi on 08.11.2021.
//
#include <sstream>
#include "phone_number.h"

PhoneNumber::PhoneNumber(const string &international_number) {
    stringstream _sstream(international_number);
    char plus, tire_1, tire_2;
    int country, city;
    string local;
    _sstream >> plus >> country >> tire_1 >> city >> tire_2 >> local;
    if (_sstream && plus == '+' && tire_1 == tire_2 && tire_1 == '-') {
        country_code_ = to_string(country);
        city_code_ = to_string(city);
        local_number_ = local;
    } else {
        throw invalid_argument("something wrong");
    }
}

string PhoneNumber::GetCountryCode() const {
    return std::string(country_code_);
}

string PhoneNumber::GetCityCode() const {
    return std::string(city_code_);
}

string PhoneNumber::GetLocalNumber() const {
    return std::string(local_number_);
}

string PhoneNumber::GetInternationalNumber() const {
    return std::string("+" + country_code_ + "-" + city_code_ + "-" + local_number_);
}
