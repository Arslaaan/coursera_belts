#include "../test_runner.h"

#include <string>
#include <vector>

using namespace std;

template <typename T>
class Deque {
public:
    Deque()= default;;

    bool Empty() const {
        return left.empty() && right.empty();
    }
    std::size_t Size() const {
        return left.size() + right.size();
    }

    T& operator[](size_t index) {
        if (index >= left.size()) {
            return right[index - left.size()];
        } else {
            return left[left.size() - 1 - index];
        }
    }
    const T& operator[](const size_t index) const {
        if (index >= left.size()) {
            return right[index - left.size()];
        } else {
            return left[left.size() - 1 - index];
        }
    }

    T& At(size_t index) {
        if (index >= left.size()) {
            return right.at(index - left.size());
        } else {
            return left.at(left.size() - 1 - index);
        }
    }
    const T& At(const size_t index) const {
        if (index >= left.size()) {
            return right.at(index - left.size());
        } else {
            return left.at(left.size() - 1 - index);
        }
    }

    T& Front() {
        if (left.empty()) {
            return right.front();
        }
        return left.back();
    }
    const T& Front() const {
        if (left.empty()) {
            return right.front();
        }
        return left.back();
    }

    T& Back() {
        if (right.empty()) {
            return left.front();
        }
        return right.back();
    }
    const T& Back() const {
        if (right.empty()) {
            return left.front();
        }
        return right.back();
    }

    void PushBack(const T& v) {
        right.push_back(v);
    }
    void PushFront(const T& v) {
        left.push_back(v);
    }
private:
    vector<T> left;
    vector<T> right;
};

void testDeque() {
    {
        Deque<int> deque;

        ASSERT(deque.Empty());
        ASSERT_EQUAL(deque.Size(), 0u);
    }
    {
        Deque<int> deque;
        deque.PushBack(0);
        deque.PushBack(1);

        ASSERT_EQUAL(deque[0], 0);
        ASSERT_EQUAL(deque[1], 1);
        ASSERT_EQUAL(deque.Size(), 2u);
    }
    {
        Deque<int> deque;
        deque.PushBack(0);

        ASSERT_EQUAL(deque[0], 0);
        ASSERT_EQUAL(deque.At(0), 0);
        ASSERT_EQUAL(deque.Size(), 1u);
    }
    {
        Deque<int> deque;
        deque.PushFront(0);
        deque.PushFront(1);
        deque.PushFront(2);
        deque.PushFront(3);
        deque.PushFront(4);

        ASSERT_EQUAL(deque[0], 4);
        ASSERT_EQUAL(deque[1], 3);
        ASSERT_EQUAL(deque[2], 2);
        ASSERT_EQUAL(deque[3], 1);
        ASSERT_EQUAL(deque[4], 0);
        ASSERT_EQUAL(deque.Front(), 4);
        ASSERT_EQUAL(deque.Back(), 0);
        ASSERT_EQUAL(deque.Size(), 5u);
    }
    {
        Deque<int> deque;
        deque.PushFront(0);
        deque.PushFront(1);

        ASSERT_EQUAL(deque[0], 1);
        ASSERT_EQUAL(deque[1], 0);
        ASSERT_EQUAL(deque.Size(), 2u);
    }
    {
        Deque<int> deque;
        deque.PushBack(0);
        deque.PushBack(1);
        deque.PushFront(-1);
        deque.PushFront(-5);

        ASSERT_EQUAL(deque[0], -5);
        ASSERT_EQUAL(deque[1], -1);
        ASSERT_EQUAL(deque[2], 0);
        ASSERT_EQUAL(deque[3], 1);

        ASSERT_EQUAL(deque.Back(), 1);
        ASSERT_EQUAL(deque.Front(), -5);

        ASSERT_EQUAL(deque.Size(), 4u);
    }
    {
        Deque<int> deque;
        deque.PushBack(0);
        deque.PushBack(1);
        deque.PushFront(-1);
        deque.PushFront(-5);

        ASSERT_EQUAL(deque.At(0), -5);
        ASSERT_EQUAL(deque.At(1), -1);
        ASSERT_EQUAL(deque.At(2), 0);
        ASSERT_EQUAL(deque.At(3), 1);

        ASSERT_EQUAL(deque.Back(), 1);
        ASSERT_EQUAL(deque.Front(), -5);

        ASSERT_EQUAL(deque.Size(), 4u);
    }
    {
        Deque<int> deque;
        bool catched = false;
        deque.PushBack(0);
        deque.PushFront(-1);
        deque.PushFront(100);

        ASSERT_EQUAL(deque.At(0), 100);
        ASSERT_EQUAL(deque.At(1), -1);
        ASSERT_EQUAL(deque.At(2), 0);
        ASSERT_EQUAL(deque.Size(), 3u);
        try {
            ASSERT_EQUAL(deque.At(3), 1);
        } catch (out_of_range& e) {
            catched = true;
        }
        ASSERT(catched);
    }
    {
        Deque<int> deque;
        bool catched = false;
        deque.PushBack(0);
        deque.PushFront(-1);
        deque.PushFront(100);

        ASSERT_EQUAL(deque.At(0), 100);
        ASSERT_EQUAL(deque.At(1), -1);
        ASSERT_EQUAL(deque.At(2), 0);
        ASSERT_EQUAL(deque.Size(), 3u);
        try {
            ASSERT_EQUAL(deque.At(-1), 1);
        } catch (out_of_range& e) {
            catched = true;
        }
        ASSERT(catched);
    }
    {
        Deque<int> deque;
        bool catched = false;
        deque.PushBack(0);
        deque.PushFront(-1);
        deque.PushFront(100);

        ASSERT_EQUAL(deque.At(0), 100);
        ASSERT_EQUAL(deque.At(1), -1);
        ASSERT_EQUAL(deque.At(2), 0);
        ASSERT_EQUAL(deque.Size(), 3u);
        try {
            ASSERT_EQUAL(deque.At(100), 1);
        } catch (out_of_range& e) {
            catched = true;
        }
        ASSERT(catched);
    }
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, testDeque);
    return 0;
}