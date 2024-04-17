#include <vector>
#include <iostream>

using namespace std;

class Node {
private:
    int value;
    vector<pair<Node*, int>> edges; 
    Node* parent; 
    int rank;
public:
    Node(int newValue);
    void Attach(Node* node, int weight);
    int GetValue(); 
    int SetValue(int newValue);
    vector<pair<Node*,int>> GetEdges();
    Node* GetParent();
    void SetParent(Node* p); 
    int GetRank(); 
    void SetRank(int r);
};

Node::Node(int newValue) {
    value = newValue;
    parent = nullptr;
    rank = 0;
}

void Node::Attach(Node* node, int weight) {
    edges.emplace_back(node, weight);
}

int Node::GetValue() {
    return value;
}

int Node::SetValue(int newValue) {
    value = newValue;
}

vector<pair<Node*,int>> Node::GetEdges() {
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
