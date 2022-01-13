#include "command_handler.h"

void commandHandler(Database& db, istream& input_stream, ostream& output_stream) {
    for (string line; getline(input_stream, line);) {
        istringstream is(line);

        string command;
        is >> command;
        if (command == "Add") {
            const auto date = ParseDate(is);
            const auto event = ParseEvent(is);
            db.Add(date, event);
        } else if (command == "Print") {
            db.Print(output_stream);
        } else if (command == "Del") {
            auto condition = ParseCondition(is);
            auto predicate = [condition](const Date &date, const string &event) {
                return condition->Evaluate(date, event);
            };
            int count = db.RemoveIf(predicate);
            output_stream << "Removed " << count << " entries" << endl;
        } else if (command == "Find") {
            auto condition = ParseCondition(is);
            auto predicate = [condition](const Date &date, const string &event) {
                return condition->Evaluate(date, event);
            };

            const auto entries = db.FindIf(predicate);
            for (const auto &entry : entries) {
                output_stream << entry << endl;
            }
            output_stream <<  "Found " << entries.size() << " entries" << endl;
        } else if (command == "Last") {
            try {
                output_stream << db.Last(ParseDate(is)) << endl;
            } catch (invalid_argument &) {
                output_stream << "No entries" << endl;
            }
        } else if (command.empty()) {
            continue;
        } else {
            throw logic_error("Unknown command: " + command);
        }
    }
}