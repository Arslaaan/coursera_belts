#include "event_parser.h"

std::string ParseEvent(std::istream &is) {
    // Р РµР°Р»РёР·СѓР№С‚Рµ СЌС‚Сѓ С„СѓРЅРєС†РёСЋ
    std::string result;
    getline(is, result);
    std::stringstream ss(result);
    getline(ss >> std::ws, result);
    return result;
}