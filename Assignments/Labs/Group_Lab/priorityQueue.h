// *************************************************************************
//  Class: Priority Queue (header)
//
//  Description: Priority Queue stores Patients based on their severity
//               the more sever the injury, the quicker they are dequed
//               and sent to a room.
//
// *************************************************************************
#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include "room.h"
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