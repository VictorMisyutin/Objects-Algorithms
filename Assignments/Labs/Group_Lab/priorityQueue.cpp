#include "PriorityQueue.h"
PriorityQueue::PriorityQueue() {
    queue = {};
}
void PriorityQueue::enqueue(Patient* n) {
    queue.push_back(n);
    sort(queue.begin(), queue.end(), [](Patient* a, Patient* b) {
        return a->GetSeverity() > b->GetSeverity();
    });
}
Patient* PriorityQueue::peek() {
    return queue[0];
}
Patient* PriorityQueue::pop() {
    Patient* result = queue[0];
    queue.erase(queue.begin());
    return result;
}
void PriorityQueue::Print() {
    for (Patient* p : queue) {
        p->Print();
    }
}
bool PriorityQueue::IsEmpty() {
    return queue.size() == 0;
}
int PriorityQueue::Size() {
    return queue.size();
}
bool PriorityQueue::Contains(Patient* n) {
    for (Patient* Patient : queue) {
        if (Patient == n) {
            return true;
        }
    }
    return false;
}