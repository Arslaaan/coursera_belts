#include "../test_runner.h"

using namespace std;

// Реализуйте здесь шаблонный класс Table

template <typename T>
class Table {
public:
    Table<T>(size_t row_size, size_t col_size) {
        Resize(row_size, col_size);
    };

    [[nodiscard]] pair<size_t, size_t> Size() const {
        if (data.empty() || data.at(0).empty()) {
            return make_pair(0, 0);
        } else {
            return make_pair(data.size(), data.at(0).size());
        }
    }

    void Resize(size_t i, size_t j) {
        data.resize(i);
        for(auto& row: data) {
            row.resize(j);
        }
    }

    vector<T>& operator[](size_t i) {
        return data[i];
    }
    const vector<T>& operator[](size_t i) const {
        return data.at(i);
    }
private:
    vector<vector<T>> data;
};

void TestTable() {
    {
        Table<int> t(1, 1);
        ASSERT_EQUAL(t.Size().first, 1u);
        ASSERT_EQUAL(t.Size().second, 1u);
        t[0][0] = 42;
        ASSERT_EQUAL(t[0][0], 42);
        t.Resize(3, 4);
        ASSERT_EQUAL(t.Size().first, 3u);
        ASSERT_EQUAL(t.Size().second, 4u);
        t.Resize(0, 0);
        ASSERT_EQUAL(t.Size().first, 0u);
        ASSERT_EQUAL(t.Size().second, 0u);
    }
    {
        Table<int> t(0, 0);
        ASSERT_EQUAL(t.Size().first, 0u);
        ASSERT_EQUAL(t.Size().second, 0u);

        Table<int> w(0, 1);
        ASSERT_EQUAL(w.Size().first, 0u);
        ASSERT_EQUAL(w.Size().second, 0u);

        Table<int> z(1, 0);
        ASSERT_EQUAL(z.Size().first, 0u);
        ASSERT_EQUAL(z.Size().second, 0u);
    }
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestTable);
  return 0;
}
