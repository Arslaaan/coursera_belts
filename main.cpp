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
};

bool operator==(const Rational& r1, const Rational& r2) {
    return r1.Numerator() == r2.Numerator() && r1.Denominator() == r2.Denominator();
}

Rational operator+(const Rational& r1, const Rational& r2) {
    return Rational(r1.Numerator()*r2.Denominator() + r2.Numerator()*r1.Denominator(), r1.Denominator()*r2.Denominator());
}

Rational operator-(const Rational& r1, const Rational& r2) {
    return Rational(r1.Numerator()*r2.Denominator() - r2.Numerator()*r1.Denominator(), r1.Denominator()*r2.Denominator());
}

Rational operator*(const Rational& r1, const Rational& r2) {
    return Rational(r1.Numerator()*r2.Numerator(), r1.Denominator()*r2.Denominator());
}

Rational operator/(const Rational& r1, const Rational& r2) {
    return Rational(r1.Numerator()*r2.Denominator(), r1.Denominator()*r2.Numerator());
}

int main() {
    {
        Rational a(2, 3);
        Rational b(4, 3);
        Rational c = a * b;
        bool equal = c == Rational(8, 9);
        if (!equal) {
            cout << "2/3 * 4/3 != 8/9" << endl;
            return 1;
        }
    }

    {
        Rational a(5, 4);
        Rational b(15, 8);
        Rational c = a / b;
        bool equal = c == Rational(2, 3);
        if (!equal) {
            cout << "5/4 / 15/8 != 2/3" << endl;
            return 2;
        }
    }

    cout << "OK" << endl;
    return 0;
}