#include <vector>

using namespace std;

class Node {
// private:
private:
    int value; // store the value of the node
    vector<pair<Node*, int>> edges; // keep track of nodes connected to this node and the weight of each edge
public:
    Node(int newValue);
    void Attach(Node* node, int weight); // attach node to another node and record the weight of that edge
    int GetValue(); // get value of node
};
Node::Node(int newValue){
    value = newValue;
}

void Node::Attach(Node* node, int weight){
    pair<Node*, int> pair;
    pair.first = node;
    pair.second = weight; 
    edges.push_back(pair);
    return;
}

int Node::GetValue(){
    return value;
}
// void Heap<Comparable>::percolateUp(const Comparable& item)