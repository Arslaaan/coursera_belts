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

ostream &operator<<(ostream &os, const Rational &rational) {
    os << rational.p << "/" << rational.q;
    return os;
}

istream &operator>>(istream &is, Rational &rational) {
    int p, q = -939393939;
    if (!is.eof()) {
        is >> p;
        if (!is.eof()) {
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
        ostringstream output;
        output << Rational(-6, 8);
        if (output.str() != "-3/4") {
            cout << "Rational(-6, 8) should be written as \"-3/4\"" << endl;
            return 1;
        }
    }

    {
        istringstream input("5/7");
        Rational r;
        input >> r;
        bool equal = r == Rational(5, 7);
        if (!equal) {
            cout << "5/7 is incorrectly read as " << r << endl;
            return 2;
        }
    }

    {
        istringstream input("");
        Rational r;
        bool correct = !(input >> r);
        if (!correct) {
            cout << "Read from empty stream works incorrectly" << endl;
            return 3;
        }
    }

    {
        istringstream input("5/7 10/8");
        Rational r1, r2;
        input >> r1 >> r2;
        bool correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct) {
            cout << "Multiple values are read incorrectly: " << r1 << " " << r2 << endl;
            return 4;
        }

        input >> r1;
        input >> r2;
        correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct) {
            cout << "Read from empty stream shouldn't change arguments: " << r1 << " " << r2 << endl;
            return 5;
        }
    }

    {
        istringstream input1("1*2"), input2("1/"), input3("/4");
        Rational r1, r2, r3;
        input1 >> r1;
        input2 >> r2;
        input3 >> r3;
        bool correct = r1 == Rational() && r2 == Rational() && r3 == Rational();
        if (!correct) {
            cout << "Reading of incorrectly formatted rationals shouldn't change arguments: "
                 << r1 << " " << r2 << " " << r3 << endl;

            return 6;
        }
    }

    cout << "OK" << endl;
    return 0;
}