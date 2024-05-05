#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include "patient.h"
using namespace std;

class PriorityQueue {
public:
    PriorityQueue();
    void enqueue(Patient* p);
    Patient* peek();
    Patient* pop(); 
    void Print();
    bool IsEmpty();
    int Size();
    bool Contains(Patient* p);
private:
    vector<Patient*> queue;
};
#endif