#include "event_parser.h"

std::string ParseEvent(std::istream &is) {
    std::string result;
    getline(is, result);
    std::stringstream ss(result);
    getline(ss >> std::ws, result);
    return result;
}