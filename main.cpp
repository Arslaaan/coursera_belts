#include <iostream>
#include <stdexcept>
#include "database.h"
#include "condition_parser.h"
#include "test_runner.h"
#include "command_handler.h"

using namespace std;

void TestAll() {
    TestRunner tr;
    tr.RunTest(TestParseEvent, "TestParseEvent");
    tr.RunTest(TestParseCondition, "TestParseCondition");
    tr.RunTest(TestTaskExamples, "TestTaskExamples");
}

int main() {
    TestAll();

    Database db;
    commandHandler(db, cin, cout);

    return 0;
}