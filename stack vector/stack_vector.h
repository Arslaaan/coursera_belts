#pragma once

#include <stdexcept>
#include <array>
using namespace std;

template <typename T, size_t N>
class StackVector {
public:
    explicit StackVector(size_t a_size = 0) : size(a_size) {
        if (a_size > N) {
            throw invalid_argument("");
        }
    };

    T& operator[](size_t index) {
        return array_[index];
    }
    const T& operator[](size_t index) const {
        return array_[index];
    }

    typename array<T, N>::iterator begin() {
        return array_.begin();
    }
    typename array<T, N>::iterator end() {
        auto it = array_.begin();
        advance(it, size);
        return it;
    }
    typename array<T, N>::const_iterator begin() const {
        return array_.begin();
    }
    typename array<T, N>::const_iterator end() const {
        auto it = array_.begin();
        advance(it, size);
        return it;
    }

    size_t Size() const {
        return size;
    }
    size_t Capacity() const {
        return N;
    }

    void PushBack(const T& value) {
        if (size == N) {
            throw overflow_error("");
        }
        size++;
        array_[size - 1] = value;
    }
    T PopBack() {
        if (size == 0) {
            throw underflow_error("");
        }
        size--;
        return array_[size];
    }

private:
    size_t size;
    array<T, N> array_;
};
