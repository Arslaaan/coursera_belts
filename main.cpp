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

int NOD(int p, int q) {
    p = abs(p);
    q = abs(q);
    while (p != 0 && q != 0) {
        if (p > q) {
            p = p % q;
        } else {
            q = q % p;
        }
    }
    return p + q;
}

class Rational {
    int p;
    int q;
public:
    Rational() {
        p = 0;
        q = 1;
    }

    Rational(int numerator, int denominator) {
        p = numerator;
        q = denominator;
        if (p == 0) {
            q = 1;
        } else if ((double) p / q < 0) {
            p = -abs(p);
            q = abs(q);
        } else {
            p = abs(p);
            q = abs(q);
        }
        int nod = NOD(p, q);
        while (nod != 1) {
            p /= nod;
            q /= nod;
            nod = NOD(p, q);
        }
    }

    int Numerator() const {
        return p;
    }

    int Denominator() const {
        return q;
    }

    friend ostream &operator<<(ostream &os, const Rational &rational);
};

bool operator==(const Rational &r1, const Rational &r2) {
    return r1.Numerator() == r2.Numerator() && r1.Denominator() == r2.Denominator();
}

Rational operator+(const Rational &r1, const Rational &r2) {
    return Rational(r1.Numerator() * r2.Denominator() + r2.Numerator() * r1.Denominator(),
                    r1.Denominator() * r2.Denominator());
}

Rational operator-(const Rational &r1, const Rational &r2) {
    return Rational(r1.Numerator() * r2.Denominator() - r2.Numerator() * r1.Denominator(),
                    r1.Denominator() * r2.Denominator());
}

Rational operator*(const Rational &r1, const Rational &r2) {
    return Rational(r1.Numerator() * r2.Numerator(), r1.Denominator() * r2.Denominator());
}

Rational operator/(const Rational &r1, const Rational &r2) {
    return Rational(r1.Numerator() * r2.Denominator(), r1.Denominator() * r2.Numerator());
}

bool operator<(const Rational &r1, const Rational &r2) {
    Rational r = r1 / r2;
    return r.Numerator() / r.Denominator() < 1.0;
}

ostream &operator<<(ostream &os, const Rational &rational) {
    os << rational.p << "/" << rational.q;
    return os;
}

istream &operator>>(istream &is, Rational &rational) {
    int p, q;
    if (is) {
        is >> p;
        if (is) {
            string d;
            is >> d;
            if (d[0] == '/' && d.size() > 1) {
                stringstream ss(d.substr(1, d.size() - 1));
                ss >> q;
                rational = Rational(p, q);
            }
        }
    }
    return is;
}

int main() {
    {
        const set<Rational> rs = {{1, 2}, {1, 25}, {3, 4}, {3, 4}, {1, 2}};
        if (rs.size() != 3) {
            cout << "Wrong amount of items in the set" << endl;
            return 1;
        }

        vector<Rational> v;
        for (auto x : rs) {
            v.push_back(x);
        }
        if (v != vector<Rational>{{1, 25}, {1, 2}, {3, 4}}) {
            cout << "Rationals comparison works incorrectly" << endl;
            return 2;
        }
    }

    {
        map<Rational, int> count;
        ++count[{1, 2}];
        ++count[{1, 2}];

        ++count[{2, 3}];

        if (count.size() != 2) {
            cout << "Wrong amount of items in the map" << endl;
            return 3;
        }
    }

    cout << "OK" << endl;
    return 0;
}