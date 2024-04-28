#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include "Node.h"
using namespace std;

class PriorityQueue {
private:
    vector<Node*> queue;
public:
    PriorityQueue();
    void enqueue(Node* n);
    Node* peek();
    Node* pop(); 
    void Print(ofstream& file);
    bool IsEmpty();
    int Size();
    bool Contains(Node* n);
};
#endif