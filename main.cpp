#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

class Matrix {
    vector<vector<int>> data;
public:
    Matrix() {
        vector<int> emptyRow(0);
        data.push_back(emptyRow);
    }

    Matrix(const int rowSize, const int colSize) {
        if (rowSize < 0 || colSize < 0) {
            throw out_of_range("matrix constructor");
        }
        for (int i = 0; i < rowSize; ++i) {
            vector<int> row(colSize);
            data.push_back(row);
        }
    }

    void Reset(const int rowSize, const int colSize) {
        if (rowSize < 0 || colSize < 0) {
            throw out_of_range("reset");
        }
        for (auto &row: data) {
            row.clear();
        }
        data.clear();
        for (int i = 0; i < rowSize; ++i) {
            vector<int> row(colSize);
            data.push_back(row);
        }
    }

    int At(const int i, const int j) const {
        if (i < 0 || i >= GetNumRows() || j < 0 || j >= GetNumColumns()) {
            throw out_of_range("at");
        }
        return data[i][j];
    }

    int &At(const int i, const int j) {
        if (i < 0 || i >= GetNumRows() || j < 0 || j >= GetNumColumns()) {
            throw out_of_range(to_string(i) + " " + to_string(j));
        }
        return data[i][j];
    }

    int GetNumColumns() const {
        if (!data.empty()) {
            return data[0].size();
        } else {
            return 0;
        }
    }

    int GetNumRows() const {
        if (GetNumColumns() == 0) {
            return 0;
        }
        return data.size();
    }
};

istream &operator>>(istream &in, Matrix &matrix) {
    int row_size, col_size;
    in >> row_size >> col_size;
    Matrix newMatrix(row_size, col_size);
    for (int i = 0; i < row_size; ++i) {
        for (int j = 0; j < col_size; ++j) {
            in >> newMatrix.At(i, j);
        }
    }
    if (in) {
        matrix = newMatrix;
    }
    return in;
}

ostream &operator<<(ostream &out, const Matrix &matrix) {
    out << matrix.GetNumRows() << " " << matrix.GetNumColumns() << endl;
    for (int i = 0; i < matrix.GetNumRows(); ++i) {
        for (int j = 0; j < matrix.GetNumColumns(); ++j) {
            out << matrix.At(i, j) << " ";
        }
        out << endl;
    }
    return out;
}

bool operator==(const Matrix &m1, const Matrix &m2) {
    if (m1.GetNumRows() != m2.GetNumRows() || m1.GetNumColumns() != m2.GetNumColumns()) {
        return false;
    }
    for (int i = 0; i < m1.GetNumRows(); ++i) {
        for (int j = 0; j < m1.GetNumColumns(); ++j) {
            if (m1.At(i, j) != m2.At(i, j)) {
                return false;
            }
        }
    }
    return true;
}

Matrix operator+(const Matrix &m1, const Matrix &m2) {
    if (m1.GetNumRows() != m2.GetNumRows() || m1.GetNumColumns() != m2.GetNumColumns()) {
        throw invalid_argument("");
    }
    Matrix result(m1.GetNumRows(), m1.GetNumColumns());
    for (int i = 0; i < m1.GetNumRows(); ++i) {
        for (int j = 0; j < m1.GetNumColumns(); ++j) {
            result.At(i, j) = m1.At(i, j) + m2.At(i, j);
        }
    }
    return result;
}

int main() {
    Matrix one;

    return 0;
}