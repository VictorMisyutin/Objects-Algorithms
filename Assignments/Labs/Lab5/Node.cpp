#include "Node.h"
void Node::Attach(Node* node, int weight) {
    edges.emplace_back(node, weight);
}

int Node::GetValue() {
    return value;
}

void Node::SetValue(int newValue) {
    value = newValue;
}

vector<pair<Node*, int>> Node::GetEdges() {
    return edges;
}

Node* Node::GetParent() {
    return parent;
}

void Node::SetParent(Node* p) {
    parent = p;
}

int Node::GetRank() {
    return rank;
}

void Node::SetRank(int r) {
    rank = r;
}
