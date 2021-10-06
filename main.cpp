#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <fstream>
#include <iomanip>

using namespace std;

struct Student {
    string name;
    string surname;
    int day;
    int month;
    int year;
};

void PrintError() {
    cout << "bad request" << endl;
}

bool CorrectName(const string &name) {
    return name.size() >= 1 && name.size() <= 15;
}

bool CorrectDate(const int &date) {
    return date >= 0 && date <= 1000000000;
}

int main() {
    vector<Student> students;
    int n, m;
    cin >> n;
    if (n < 0 || n > 10000) {
        PrintError();
        return 0;
    }
    for (int i = 0; i < n; ++i) {
        string name, surname;
        int day, month, year;
        cin >> name >> surname >> day >> month >> year;
        if (CorrectName(name) && CorrectName(surname) &&
            CorrectDate(day) && CorrectDate(month) && CorrectDate(year)) {
            students.push_back({name, surname, day, month, year});
        } else {
            PrintError();
        }
    }
    cin >> m;
    if (m < 0 || m > 10000) {
        PrintError();
        return 0;
    }
    for (int i = 0; i < m; ++i) {
        string request;
        int number;
        cin >> request >> number;
        if (CorrectDate(number) && CorrectName(request) && number >= 1 && number <= n) {
            if (request == "name") {
                cout << students[number - 1].name << " " << students[number - 1].surname << endl;
            } else if (request == "date") {
                Student student = students[number - 1];
                cout << student.day << "." << student.month << "." << student.year << endl;
            } else {
                PrintError();
            }
        } else {
            PrintError();
        }
    }
    return 0;
}