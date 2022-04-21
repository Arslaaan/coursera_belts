#include "stats.h"

const map<string_view, int> &Stats::GetUriStats() const {
    return uriStats;
}

const map<string_view, int> &Stats::GetMethodStats() const {
    return methodStats;
}

void Stats::AddUri(string_view uri) {
    if (acceptableUri.count(uri) == 0) {
        uriStats[UNKNOWN_URI]++;
        return;
    }
    uriStats[uri]++;
}

void Stats::AddMethod(string_view method) {
    if (acceptableMethods.count(method) == 0) {
        methodStats[UNKNOWN_METHOD]++;
        return;
    }
    methodStats[method]++;
}

Stats::Stats() {
    for (auto &uri: acceptableUri) {
        uriStats[uri] = 0;
    }
    uriStats[UNKNOWN_URI] = 0;
    for (auto &method: acceptableMethods) {
        methodStats[method] = 0;
    }
    methodStats[UNKNOWN_METHOD] = 0;
}

HttpRequest ParseRequest(string_view line) {
    string_view result[3];
    int i = 0;
    while (line.find(' ') == 0) {
        line.remove_prefix(1);
    }
    while (true) {
        size_t space = line.find(' ');
        result[i++] = line.substr(0, space);
        if (space == string_view::npos) {
            break;
        } else {
            line.remove_prefix(space + 1);
        }
    }

    return {result[0], result[1], result[2]};
}
