#include "Node.cpp"

class Edge {
public:
    Node* node1;
    Node* node2;
    int weight;

    Edge(Node* n1, Node* n2, int w) : node1(n1), node2(n2), weight(w) {}
};