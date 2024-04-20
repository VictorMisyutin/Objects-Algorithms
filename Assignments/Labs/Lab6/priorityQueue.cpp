#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include "Node.cpp"
using namespace std;

class PriorityQueue{
private:
    vector<Node*> queue;
public:
    PriorityQueue(); // 
    void enqueue(Node* n); //
    Node* peek(); //
    Node* pop(); // 
    void Print(ofstream& file); //
    bool IsEmpty(); //
    int Size(); //
    bool Contains(Node* n); //
};
PriorityQueue::PriorityQueue(){
    queue = {};
}
void PriorityQueue::enqueue(Node* n){
    queue.push_back(n);
    sort(queue.begin(), queue.end(), [](Node* a, Node* b) {
        if(a->GetFrequency() == b->GetFrequency()){
          return a->GetAsciiCode() < b->GetAsciiCode();
        }
        return a->GetFrequency() < b->GetFrequency();
    });
}
Node* PriorityQueue::peek(){
    return queue[0];
}
Node* PriorityQueue::pop(){
    Node* result = queue[0];
    queue.erase(queue.begin());
    return result;
}
void PriorityQueue::Print(ofstream& file){
    for(Node* n : queue){
        file << n->GetAsciiCode() << " '" << n->GetCharacter() << "' {" << n->GetFrequency() << "}" << endl;
    }
}
bool PriorityQueue::IsEmpty(){
    return queue.size() == 0;
}
int PriorityQueue::Size(){
    return queue.size();
}
bool PriorityQueue::Contains(Node* n){
    for(Node* node : queue){
        if(node == n){
            return true;
        }
    }
    return false;
}