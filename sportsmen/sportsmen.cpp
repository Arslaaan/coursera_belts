#include "../test_runner.h"
#include <list>
#include <algorithm>

using namespace std;

class SportsmenQueue {
public:
    void updateQueue(int currentIdx, int beforeCurrentIdxNeeded) {
        const auto afterCurrentIt = released.find(beforeCurrentIdxNeeded);
        if (afterCurrentIt != released.end()) {
            queue.splice(next(afterCurrentIt->second), {currentIdx});
            released[currentIdx] = next(afterCurrentIt->second);
        } else {
            queue.push_front(currentIdx);
            released[currentIdx] = queue.begin();
        }
    }
    void print() {
        for(auto it = queue.rbegin();it != queue.rend();++it) {
            cout << *it << endl;
        }
    }
private:
    list<int> queue;
    map<int, list<int>::const_iterator> released;
};


int main() {
    int q;
    cin >> q;
    SportsmenQueue sportsmenQueue;
    for (int i = 0;i < q; ++i) {
        int idx, idxBefore;
        cin >> idx >> idxBefore;
        sportsmenQueue.updateQueue(idx, idxBefore);
    }
    sportsmenQueue.print();

}