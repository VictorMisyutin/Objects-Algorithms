#ifndef NODE_H
#define NODE_H

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
    Node(int newValue): value(newValue), parent(nullptr), rank(0){};
    void Attach(Node* node, int weight);
    int GetValue();
    void SetValue(int newValue);
    vector<pair<Node*, int>> GetEdges();
    Node* GetParent();
    void SetParent(Node* p);
    int GetRank();
    void SetRank(int r);
};

#endif