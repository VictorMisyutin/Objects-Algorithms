#include <vector>
#include <algorithm>
#include "character.cpp"

using namespace std;

class PriorityQueue{
private:
    vector<Character> queue;
public:
    PriorityQueue();
    void Insert(Character c);
    Character peek();
    Character pop();
    void Print();
    bool IsEmpty();
    int Size();
    bool Contains(string c);
};

void PriorityQueue::Insert(Character c){
    // append item to queue
    queue.push_back(c);
    // sort in reverse order based on frequency
    // queue.sort()
    sort(queue.begin(), queue.end(), [](Character &a, Character &b) {
        return a.GetFrequency() > b.GetFrequency();
    });
}
