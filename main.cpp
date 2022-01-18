#include <iostream>
#include "database.h"
#include "test_runner.h"
#include "test_db.h"

using namespace std;

void TestAll() {
    TestRunner tr;
    tr.RunTest(TestDateComparisonNode, "TestDateComparisonNode");
    tr.RunTest(TestEventComparisonNode, "TestEventComparisonNode");
    tr.RunTest(TestLogicalOperationNode, "TestLogicalOperationNode");
    tr.RunTest(TestParseEvent, "TestParseEvent");
    tr.RunTest(TestParseCondition, "TestParseCondition");
    tr.RunTest(TestTaskExamples, "TestTaskExamples");
    tr.RunTest(TestEmptyNode, "TestEmptyNode");
    tr.RunTest(TestDbAdd, "TestDbAdd");
    tr.RunTest(TestDbFind, "TestDbFind");
    tr.RunTest(TestDbLast, "TestDbLast");
    tr.RunTest(TestDbRemoveIf, "TestDbRemoveIf");
    tr.RunTest(TestInsertionOrder, "TestInsertionOrder");
    tr.RunTest(TestsMyCustom, "TestsMyCustom");
    tr.RunTest(TestDatabase, "GitHub");
}

int main() {
    TestAll();

    Database db;
    commandHandler(db, cin, cout);

    return 0;
}