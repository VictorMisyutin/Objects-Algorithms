#include <queue>
// #include "Node.cpp"
#include "PriorityQueue.cpp"

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

void MinHeap::Push(Node* node) {
    priority_queue<Node*, vector<Node*>, CompareNode> pq;

    pq.push(node);

    while (pq.size() > 1) {
        Node* left = pq.top();
        pq.pop();
        Node* right = pq.top();
        pq.pop();

        int freqSum = left->GetFrequency() + right->GetFrequency();
        Node* internalNode = new Node(-1, "", freqSum, left, right);

        pq.push(internalNode);
    }

    root = pq.top();
}
