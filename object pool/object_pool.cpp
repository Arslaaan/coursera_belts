#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>
using namespace std;

template <class T>
class ObjectPool {
public:
    T* Allocate() {
        if (poolDeallocated.empty()) {
            T* ptr = new T;
            poolAllocated.insert(ptr);
            return ptr;
        }
        T* ptr = poolDeallocated.front();
        poolDeallocated.pop_front();
        poolAllocated.insert(ptr);
        return ptr;
    }
    T* TryAllocate() {
        if (poolDeallocated.empty()) {
            return nullptr;
        }
        return Allocate();
    }

    void Deallocate(T* object) {
        auto it = poolAllocated.find(object);
        if (it == poolAllocated.end()) {
            throw invalid_argument("");
        }
        poolAllocated.erase(it);
        poolDeallocated.push_back(object);
    }

    ~ObjectPool() {
        for (auto& object: poolAllocated) {
            delete object;
        }
        for (auto& object: poolDeallocated) {
            delete object;
        }
    }

private:
    set<T*> poolAllocated; // возможно не нужен
    deque<T*> poolDeallocated;
};

void TestObjectPool() {
    ObjectPool<string> pool;

    auto p1 = pool.Allocate();
    auto p2 = pool.Allocate();
    auto p3 = pool.Allocate();

    *p1 = "first";
    *p2 = "second";
    *p3 = "third";

    pool.Deallocate(p2);
    ASSERT_EQUAL(*pool.Allocate(), "second");

    pool.Deallocate(p3);
    pool.Deallocate(p1);
    ASSERT_EQUAL(*pool.Allocate(), "third");
    ASSERT_EQUAL(*pool.Allocate(), "first");

    pool.Deallocate(p1);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestObjectPool);
    return 0;
}