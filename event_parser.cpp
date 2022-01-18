#include "event_parser.h"

std::string ParseEvent(std::istream &is) {
    std::string result;
    is >> std::ws;
    getline(is, result);
    return result;
}