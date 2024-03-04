#ifndef HEAP_HPP
#define HEAP_HPP

#include <vector>

template<typename Comparable>
class Heap {
private:
    std::vector<Comparable> heapVector; // heapVector[0] is the minimum of the heap
                                        // heapVector[0..size()-1] are heap elements

    void percolateUp(const Comparable& item);   // percolating up
    void percolateDown();                       // percolating down

public:
    Heap();                                     // default constructor

    Heap(const Heap& otherHeap);                // copy constructor
    void assignCopy(const Heap& otherHeap);     // copy assignment

    virtual ~Heap();                           // destructor

    void insert(const Comparable& element);    // calls percolateUp
    void deleteMin();                          // calls percolateDown

    int size() const;                          // heap size

    const Comparable& getElement(int index) const;
};

#include "heap.cpp" // Include the implementation file

#endif // HEAP_H
