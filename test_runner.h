#pragma once
#include <sstream>
#include <exception>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <set>

#include "condition_parser.h"
#include "event_parser.h"
#include "command_handler.h"

template<class T>
std::ostream &operator<<(std::ostream &os, const std::set <T> &s);

template<class K, class V>
std::ostream &operator<<(std::ostream &os, const std::map <K, V> &m);

template<class T, class U>
void AssertEqual(const T &t, const U &u, const std::string &hint);

template<class T, class U>
void AssertNotEqual(const T &t, const U &u, const std::string &hint);

void Assert(bool b, const std::string& hint);

class TestRunner {
public:
    template <class TestFunc>
    void RunTest(TestFunc func, const std::string& test_name);

    ~TestRunner();
private:
    int fail_count = 0;
};

template<class T>
std::ostream &operator<<(std::ostream &os, const std::set<T> &s) {
    os << "{";
    bool first = true;
    for (const auto &x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template<class T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &s) {
    os << "{";
    bool first = true;
    for (const auto &x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template<class K, class V>
std::ostream &operator<<(std::ostream &os, const std::map<K, V> &m) {
    os << "{";
    bool first = true;
    for (const auto &kv : m) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
    return os << "}";
}

template<class T, class U>
void AssertEqual(const T &t, const U &u,
                 const std::string &hint) {
    if (t != u) {
        std::ostringstream os;
        os << "Assertion failed: " << t << " != " << u
           << " hint: " << hint;
        throw std::runtime_error(os.str());
    }
}

template<class T, class U>
void AssertNotEqual(const T &t, const U &u,
                    const std::string &hint) {
    if (t == u) {
        std::ostringstream os;
        os << "Assertion failed: " << t << " != " << u
           << " hint: " << hint;
        throw std::runtime_error(os.str());
    }
}

void Assert(bool b, const std::string &hint) {
    AssertEqual(b, true, hint);
}

template <class TestFunc>
void TestRunner::RunTest(TestFunc func, const std::string &test_name) {
    try {
        func();
        std::cerr << test_name << " OK" << std::endl;
    } catch (std::runtime_error &e) {
        ++fail_count;
        std::cerr << test_name << " fail: " << e.what() << std::endl;
    }
}

TestRunner::~TestRunner() {
    if (fail_count > 0) {
        std::cerr << fail_count << " unit tests failed. Terminate" << std::endl;
        exit(1);
    }
}

void TestParseCondition() {
    {
        istringstream is("date != 2017-11-18");
        shared_ptr<Node> root = ParseCondition(is);
        Assert(root->Evaluate({2017, 1, 1}, ""), "Parse condition 1");
        Assert(!root->Evaluate({2017, 11, 18}, ""), "Parse condition 2");
    }
    {
        istringstream is(R"(event == "sport event")");
        shared_ptr<Node> root = ParseCondition(is);
        Assert(root->Evaluate({2017, 1, 1}, "sport event"), "Parse condition 3");
        Assert(!root->Evaluate({2017, 1, 1}, "holiday"), "Parse condition 4");
    }
    {
        istringstream is("date >= 2017-01-01 AND date < 2017-07-01");
        shared_ptr<Node> root = ParseCondition(is);
        Assert(root->Evaluate({2017, 1, 1}, ""), "Parse condition 5");
        Assert(root->Evaluate({2017, 3, 1}, ""), "Parse condition 6");
        Assert(root->Evaluate({2017, 6, 30}, ""), "Parse condition 7");
        Assert(!root->Evaluate({2017, 7, 1}, ""), "Parse condition 8");
        Assert(!root->Evaluate({2016, 12, 31}, ""), "Parse condition 9");
    }
    {
        istringstream is(R"(event != "sport event" AND event != "Wednesday")");
        shared_ptr<Node> root = ParseCondition(is);
        Assert(root->Evaluate({2017, 1, 1}, "holiday"), "Parse condition 10");
        Assert(!root->Evaluate({2017, 1, 1}, "sport event"), "Parse condition 11");
        Assert(!root->Evaluate({2017, 1, 1}, "Wednesday"), "Parse condition 12");
    }
    {
        istringstream is(R"(event == "holiday AND date == 2017-11-18")");
        shared_ptr<Node> root = ParseCondition(is);
        Assert(!root->Evaluate({2017, 11, 18}, "holiday"), "Parse condition 13");
        Assert(!root->Evaluate({2017, 11, 18}, "work day"), "Parse condition 14");
        Assert(root->Evaluate({1, 1, 1}, "holiday AND date == 2017-11-18"), "Parse condition 15");
    }
    {
        istringstream is(R"(((event == "holiday" AND date == 2017-01-01)))");
        shared_ptr<Node> root = ParseCondition(is);
        Assert(root->Evaluate({2017, 1, 1}, "holiday"), "Parse condition 16");
        Assert(!root->Evaluate({2017, 1, 2}, "holiday"), "Parse condition 17");
    }
    {
        istringstream is(R"(date > 2017-01-01)");
        shared_ptr<Node> root = ParseCondition(is);
        Assert(root->Evaluate({2017, 1, 2}, "workday"), "Parse test 1");
    }
    {
        istringstream is(R"(event == "holiday")");
        shared_ptr<Node> root = ParseCondition(is);
        Assert(!root->Evaluate({2017, 1, 2}, "workday"), "Parse test 2");
    }
    {
        istringstream is(R"(date < 2017-07-01)");
        shared_ptr<Node> root = ParseCondition(is);
        Assert(root->Evaluate({2017, 1, 2}, "workday"), "Parse test 3");
    }
    {
        istringstream is(R"(event == "holiday" OR date < 2017-07-01)");
        shared_ptr<Node> root = ParseCondition(is);
        Assert(root->Evaluate({2017, 1, 2}, "workday"), "Parse test 4");
    }
    {
        istringstream is(R"(date > 2017-01-01 AND (event == "holiday" OR date < 2017-07-01))");
        shared_ptr<Node> root = ParseCondition(is);
        Assert(!root->Evaluate({2016, 1, 1}, "holiday"), "Parse condition 18");
        Assert(root->Evaluate({2017, 1, 2}, "holiday"), "Parse condition 19");
        Assert(root->Evaluate({2017, 1, 2}, "workday"), "Parse condition 20");
        Assert(!root->Evaluate({2018, 1, 2}, "workday"), "Parse condition 21");
    }
    {
        istringstream is(R"(date > 2017-01-01 AND event == "holiday" OR date < 2017-07-01)");
        shared_ptr<Node> root = ParseCondition(is);
        Assert(root->Evaluate({2016, 1, 1}, "event"), "Parse condition 22");
        Assert(root->Evaluate({2017, 1, 2}, "holiday"), "Parse condition 23");
        Assert(root->Evaluate({2017, 1, 2}, "workday"), "Parse condition 24");
        Assert(!root->Evaluate({2018, 1, 2}, "workday"), "Parse condition 25");
    }
    {
        istringstream is(R"(((date == 2017-01-01 AND event == "holiday")))");
        shared_ptr<Node> root = ParseCondition(is);
        Assert(root->Evaluate({2017, 1, 1}, "holiday"), "Parse condition 26");
        Assert(!root->Evaluate({2017, 1, 2}, "holiday"), "Parse condition 27");
    }
    {
        istringstream is(R"(((event == "2017-01-01" OR date > 2016-01-01)))");
        shared_ptr<Node> root = ParseCondition(is);
        Assert(root->Evaluate({1, 1, 1}, "2017-01-01"), "Parse condition 28");
        Assert(!root->Evaluate({2016, 1, 1}, "event"), "Parse condition 29");
        Assert(root->Evaluate({2016, 1, 2}, "event"), "Parse condition 30");
    }
}

void TestParseEvent() {
    {
        istringstream is("event");
        AssertEqual(ParseEvent(is), "event", "Parse event without leading spaces");
    }
    {
        istringstream is("   sport event ");
        AssertEqual(ParseEvent(is), "sport event ", "Parse event with leading spaces");
    }
    {
        istringstream is("  first event  \n  second event");
        vector<string> events;
        events.push_back(ParseEvent(is));
        events.push_back(ParseEvent(is));
        AssertEqual(events, vector<string>{"first event  ", "second event"}, "Parse multiple events");
    }
}

void TestTaskExamples() {
    {
        try {
            istringstream is("Add 0-2-3 Kolya\n"
                             "Add 1-12-12 Kolya\n"
                             "Add 1-12-12 Sarkazi\n"
                             "Add 999-12-12 Kolya\n"
                             "Add 1000-12-12 Kolya\n"
                             "Add 9999-12-12 Kolya\n"
                             "Print\n");
            ostringstream os;
            Database db;
            commandHandler(db, is, os);
            AssertEqual(os.str(), "0000-02-03 Kolya\n0001-12-12 Kolya\n0001-12-12 Sarkazi\n0999-12-12 Kolya\n1000-12-12 Kolya\n9999-12-12 Kolya\n", "Add test");
        } catch (exception& e) {
            e.what();
        }
    }
    {
        try {
            istringstream is("Add 0-2-3 Kolya\n"
                             "Add 1-12-12 Kolya\n"
                             "Add 1-12-12 Sarkazi\n"
                             "Add 999-12-12 Kolya\n"
                             "Add 1000-12-12 Kolya\n"
                             "Add 9999-12-12 Kolya\n"
                             "Print\n");
            ostringstream os;
            Database db;
            commandHandler(db, is, os);
            AssertEqual(os.str(), "0000-02-03 Kolya\n0001-12-12 Kolya\n0001-12-12 Sarkazi\n0999-12-12 Kolya\n1000-12-12 Kolya\n9999-12-12 Kolya\n", "Add test");
        } catch (exception& e) {
            e.what();
        }
    }
    {
        try {
            istringstream is("Add 0-2-3 Kolya\n"
                             "Add 1-12-12 Kolya\n"
                             "Add 1-12-12 Sarkazi\n"
                             "Add 1000-12-12 Kolya\n"
                             "Del\n"
                             "Find\n");
            ostringstream os;
            Database db;
            commandHandler(db, is, os);
            AssertEqual(os.str(), "Removed 4 entries\n", "Add test");
        } catch (exception& e) {
            e.what();
        }
    }
    {
        try {
            istringstream is("Add 2017-06-01 1st of June\n"
                             "Add 2017-07-08 8th of July\n"
                             "Add 2017-07-08 Someone's birthday\n"
                             "Del date == 2017-07-08\n");
            ostringstream os;
            Database db;
            commandHandler(db, is, os);
            AssertEqual(os.str(), "Removed 2 entries\n", "Add test");
        } catch (exception& e) {
            e.what();
        }
    }
    {
        try {
            istringstream is("Add 2017-01-01 Holiday\n"
                             "Add 2017-03-08 Holiday\n"
                             "Add 2017-1-1 New Year\n"
                             "Add 2017-1-1 New Year\n"
                             "Print\n");
            ostringstream os;
            Database db;
            commandHandler(db, is, os);
            AssertEqual(os.str(), "2017-01-01 Holiday\n"
                                  "2017-01-01 New Year\n"
                                  "2017-03-08 Holiday\n", "Print test");
        } catch (exception& e) {
            cerr << e.what() << endl;
        }
    }
    {
        try {
            istringstream is("Add 2017-01-01 Holiday\n"
                             "Add 2017-03-08 Holiday\n"
                             "Add 2017-01-01 New Year\n"
                             "Find event != \"working day\"\n"
                             "Add 2017-05-09 Holiday\n");
            ostringstream os;
            Database db;
            commandHandler(db, is, os);
            AssertEqual(os.str(), "2017-01-01 Holiday\n"
                                  "2017-01-01 New Year\n"
                                  "2017-03-08 Holiday\n"
                                  "Found 3 entries\n", "Find test");
        } catch (exception& e) {
            cerr << e.what() << endl;
        }
    }
    {
        try {
            istringstream is("Add 2017-01-01 New Year\n"
                             "Add 2017-03-08 Holiday\n"
                             "Add 2017-01-01 Holiday\n"
                             "Last 2016-12-31\n"
                             "Last 2017-01-01\n"
                             "Last 2017-06-01\n"
                             "Add 2017-05-09 Holiday\n");
            ostringstream os;
            Database db;
            commandHandler(db, is, os);
            AssertEqual(os.str(), "No entries\n"
                                  "2017-01-01 Holiday\n"
                                  "2017-03-08 Holiday\n", "Last test");
        } catch (exception& e) {
            cerr << e.what() << endl;
        }
    }
    {
        try {
            istringstream is("Add 2017-11-21 Tuesday\n"
                             "Add 2017-11-20 Monday\n"
                             "Add 2017-11-21 Weekly meeting\n"
                             "Print\n"
                             "Find event != \"Weekly meeting\"\n"
                             "Last 2017-11-30\n"
                             "Del date > 2017-11-20\n"
                             "Last 2017-11-30\n"
                             "Last 2017-11-01\n");
            ostringstream os;
            Database db;
            commandHandler(db, is, os);
            AssertEqual(os.str(), "2017-11-20 Monday\n"
                                  "2017-11-21 Tuesday\n"
                                  "2017-11-21 Weekly meeting\n"
                                  "2017-11-20 Monday\n"
                                  "2017-11-21 Tuesday\n"
                                  "Found 2 entries\n"
                                  "2017-11-21 Weekly meeting\n"
                                  "Removed 2 entries\n"
                                  "2017-11-20 Monday\n"
                                  "No entries\n", "All test");
        } catch (exception& e) {
            cerr << e.what() << endl;
        }
    }
}
