#ifndef MINHEAP_H
#define MINHEAP_H

#include <queue>
#include "PriorityQueue.h"

class MinHeap {
private:
    Node* root;
    int length;
public:
    MinHeap() : root(nullptr), length(0) {}
    void Push(Node* node);
};
struct CompareNode {
    bool operator()(Node* a, Node* b) const {
        return a->GetFrequency() > b->GetFrequency();
    }
};
#endif