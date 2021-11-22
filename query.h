//
// Created by aochi on 10.11.2021.
//

#ifndef COURSERA_QUERY_H
#define COURSERA_QUERY_H

#endif //COURSERA_QUERY_H

#include <string>
#include <vector>
#include <iostream>


enum class QueryType {
    NewBus,
    BusesForStop,
    StopsForBus,
    AllBuses
};

struct Query {
    QueryType type;
    std::string bus;
    std::string stop;
    std::vector<std::string> stops;
};

std::istream& operator >> (std::istream& is, Query& q);