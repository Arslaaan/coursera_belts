#include <iostream>
#include <memory>
#include <stack>
#include <vector>
#include <string>
#include <cstdint>
#include <sstream>
#include <cmath>
#include <iomanip>

using namespace std;

class Figure {
    vector<int> edges;
public:
    virtual string Name() = 0;
    virtual double Perimeter() = 0;
    virtual double Area() = 0;
protected:
    vector<int> getEdges() const {
        return edges;
    }
    void addEdge(double edge) {
        edges.push_back(edge);
    }
};

class Triangle : public Figure {
public:
    Triangle(int i, int i1, int i2) {
        addEdge(i);
        addEdge(i1);
        addEdge(i2);
    }
    string Name() override {
        return "TRIANGLE";
    }
    double Perimeter() override {
        double sum = 0.0;
        for (int i = 0; i < 3; ++i) {
            sum += getEdges()[i];
        }
        return sum;
    }
    double Area() override {
        double p = Perimeter() / 2.0;
        return sqrt(p * (p - getEdges()[0]) * (p - getEdges()[1]) * (p - getEdges()[2]));
    }
};

class Rect : public Figure {
public:
    Rect(int a, int b) {
        addEdge(a);
        addEdge(b);
    }
    string Name() override {
        return "RECT";
    }
    double Perimeter() override {
        double sum = 0.0;
        for (int i = 0; i < 2; ++i) {
            sum += getEdges()[i];
        }
        return sum * 2;
    }
    double Area() override {
        return getEdges()[0] * getEdges()[1];
    }
};

class Circle : public Figure {
    double pi = 3.14;
public:
    Circle(int r) {
        addEdge(r);
    }
    string Name() override {
        return "CIRCLE";
    }
    double Perimeter() override {
        return 2 * pi * getEdges()[0];
    }
    double Area() override {
        return pi * getEdges()[0] * getEdges()[0];
    }
};

shared_ptr<Figure> CreateFigure(istream& is) {
    string type;
    is >> type;
    if (type == "RECT") {
        int a, b;
        is >> a >> b;
        return make_shared<Rect>(a, b);
    } else if (type == "CIRCLE") {
        int r;
        is >> r;
        return make_shared<Circle>(r);
    } else if (type == "TRIANGLE") {
        int a, b, c;
        is >> a >> b >> c;
        return make_shared<Triangle>(a, b, c);
    }
}

int main() {
    vector<shared_ptr<Figure>> figures;
    for (string line; getline(cin, line); ) {
        istringstream is(line);

        string command;
        is >> command;
        if (command == "ADD") {
            // Пропускаем "лишние" ведущие пробелы.
            // Подробнее об std::ws можно узнать здесь:
            // https://en.cppreference.com/w/cpp/io/manip/ws
            is >> ws;
            figures.push_back(CreateFigure(is));
        } else if (command == "PRINT") {
            for (const auto& current_figure : figures) {
                cout << fixed << setprecision(3)
                     << current_figure->Name() << " "
                     << current_figure->Perimeter() << " "
                     << current_figure->Area() << endl;
            }
        }
    }
    return 0;
}