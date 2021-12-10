#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

template<typename T>
void print(const vector<T> &v) {
    for (size_t i = 0; i < v.size(); ++i) {
        cout << v[i] << " ";
    }
    cout << endl;
}

int main() {
    int n, q;
    cin >> n >> q;

    vector<char> operations = {'.'};
    string result = to_string(n);

    result.reserve(5 * q + 3);
    operations.reserve(q);

    int left_brace_count = 0;
    for (int i = 0; i < q; ++i) {
        char op;
        int d;
        cin >> op >> d;
        char last_op = operations.back();
        if ((op == '*' || op == '/') && (last_op == '+' || last_op == '-')){
            left_brace_count++;
            result += ") " + string(1, op) + " " + to_string(d);
        } else {
            result += " " + string(1, op) + " " + to_string(d);
        }
        operations.push_back(op);
    }
    cout << string(left_brace_count, '(') + result << endl;
    return 0;
}