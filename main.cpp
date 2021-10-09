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

int main() {
    {
        const Rational r(3, 10);
        if (r.Numerator() != 3 || r.Denominator() != 10) {
            cout << "Rational(3, 10) != 3/10" << endl;
            return 1;
        }
    }

    {
        const Rational r(8, 12);
        if (r.Numerator() != 2 || r.Denominator() != 3) {
            cout << "Rational(8, 12) != 2/3" << endl;
            return 2;
        }
    }

    {
        const Rational r(-4, 6);
        if (r.Numerator() != -2 || r.Denominator() != 3) {
            cout << "Rational(-4, 6) != -2/3" << endl;
            return 3;
        }
    }

    {
        const Rational r(4, -6);
        if (r.Numerator() != -2 || r.Denominator() != 3) {
            cout << "Rational(4, -6) != -2/3" << endl;
            return 3;
        }
    }

    {
        const Rational r(0, 15);
        if (r.Numerator() != 0 || r.Denominator() != 1) {
            cout << "Rational(0, 15) != 0/1" << endl;
            return 4;
        }
    }

    {
        const Rational defaultConstructed;
        if (defaultConstructed.Numerator() != 0 || defaultConstructed.Denominator() != 1) {
            cout << "Rational() != 0/1" << endl;
            return 5;
        }
    }

    cout << "OK" << endl;
    return 0;
}