#include "../test_runner.h"

#include <string>
#include <iterator>

using namespace std;

class Logger {
public:
    explicit Logger(ostream &output_stream) : os(output_stream) {
    }

    void SetLogLine(bool value) { log_line = value; }

    void SetLogFile(bool value) { log_file = value; }

    void SetLogFilename(const string& filename) { filename_ = filename; }

    void SetLogLineNumber(int number) { line_ = number; }

    void Log(const string &message) {
        if (log_file) {
            os << filename_;
            if (log_line) {
                os << ":" << line_;
            }
            os << " ";
        } else if (log_line) {
            os << "Line " << line_ << " ";
        }
        os << message << endl;
    }

private:
    ostream &os;
    bool log_line = false;
    bool log_file = false;
    int line_;
    string filename_;
};

#define LOG(logger, message) \
logger.SetLogFilename(__FILE__); \
logger.SetLogLineNumber(__LINE__); \
logger.Log(message);

void TestLog() {
#line 1 "logger.cpp"

    ostringstream logs;
    Logger l(logs);
    LOG(l, "hello");

    l.SetLogFile(true);
    LOG(l, "hello");

    l.SetLogLine(true);
    LOG(l, "hello");

    l.SetLogFile(false);
    LOG(l, "hello");

    string expected = "hello\n";
    expected += "logger.cpp hello\n";
    expected += "logger.cpp:10 hello\n";
    expected += "Line 13 hello\n";
    ASSERT_EQUAL(logs.str(), expected);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestLog);
}