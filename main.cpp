#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

template <typename T>
vector<T> Sqr(vector<T> vc);
template <typename Key, typename Value>
map<Key, Value> Sqr(map<Key, Value> m);
template <typename First, typename Second>
pair<First, Second> Sqr(pair<First, Second> vc);

// Объявляем шаблонные функции
template<typename T>
T Sqr(T x) {
    return x * x;
}

template <typename T>
vector<T> Sqr(vector<T> vc) {
    vector<T> result;
    for (size_t i = 0; i < vc.size(); ++i) {
        result.push_back(Sqr(vc[i]));
    }
    return result;
}

template <typename Key, typename Value>
map<Key, Value> Sqr(map<Key, Value> m) {
    map<Key, Value> result;
    for(const auto& item: m) {
        result[item.first] = Sqr(item.second);
    }
    return result;
}

template <typename First, typename Second>
pair<First, Second> Sqr(pair<First, Second> vc) {
    return make_pair(Sqr(vc.first), Sqr(vc.second));
}

int main() {
    // Пример вызова функции
    vector<int> v = {1, 2, 3};
    cout << "vector:";
    for (int x : Sqr(v)) {
        cout << ' ' << x;
    }
    cout << endl;

    map<int, pair<int, int>> map_of_pairs = {
            {4, {2, 2}},
            {7, {4, 3}}
    };
    cout << "map of pairs:" << endl;
    for (const auto &x : Sqr(map_of_pairs)) {
        cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
    }
}