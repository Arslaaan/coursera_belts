#include <iostream>
#include <string>
#include <sstream>

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

bool operator < (const Rational& lhs, const Rational& rhs) {
    return (lhs - rhs).Numerator() < 0;
}

ostream &operator<<(ostream &os, const Rational &rational) {
    os << rational.Numerator() << "/" << rational.Denominator();
    return os;
}

istream &operator>>(istream &is, Rational &r) {
    int n, d;
    char c;
    is >> n >> c >> d;
    if (is && c == '/') {
        r = Rational(n, d);
    }
    return is;
}

int main() {

    return 0;
}