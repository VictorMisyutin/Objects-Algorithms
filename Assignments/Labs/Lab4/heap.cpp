#include <vector> // Include necessary header

template<typename Comparable>
class Heap {
private:
    std::vector<Comparable> heapVector;

    void percolateUp(const Comparable& item);
    void percolateDown();

public:
    Heap();
    Heap(const Heap& otherHeap);
    void assignCopy(const Heap& otherHeap);
    ~Heap();
    void insert(const Comparable& element);
    void deleteMin();
    int size() const;
    const Comparable& getElement(int index) const;
};

template<typename Comparable>
void Heap<Comparable>::percolateUp(const Comparable& item) {
    int hole = heapVector.size() - 1; // Start at the last element
    int parent = (hole - 1) / 2; // Calculate the parent index

    while (hole > 0 && item < heapVector[parent]) {
        heapVector[hole] = heapVector[parent]; // Move the parent down
        hole = parent; // Move the hole up
        parent = (hole - 1) / 2; // Update the parent index
    }
    heapVector[hole] = item; // Place the item in the correct position
}

template<typename Comparable>
void Heap<Comparable>::percolateDown() {
    int hole = 0; // Start at the root
    int child;

    Comparable tmp = std::move(heapVector[hole]); // Save the root element

    while (hole * 2 + 1 < heapVector.size()) {
        child = hole * 2 + 1; // Left child

        // Determine the smaller child
        if (child != heapVector.size() - 1 && heapVector[child + 1] < heapVector[child])
            ++child;

        // If the smaller child is less than the element being percolated down
        if (heapVector[child] < tmp)
            heapVector[hole] = std::move(heapVector[child]); // Move the child up
        else
            break; // No need to percolate further

        hole = child; // Move the hole down
    }
    heapVector[hole] = std::move(tmp); // Place the element in the correct position
}

template<typename Comparable>
Heap<Comparable>::Heap() {}

template<typename Comparable>
Heap<Comparable>::Heap(const Heap& otherHeap) : heapVector(otherHeap.heapVector) {}

template<typename Comparable>
void Heap<Comparable>::assignCopy(const Heap& otherHeap) {
    heapVector = otherHeap.heapVector;
}

template<typename Comparable>
Heap<Comparable>::~Heap() {}

template<typename Comparable>
void Heap<Comparable>::insert(const Comparable& element) {
    heapVector.push_back(element);
    percolateUp(element);
}

template<typename Comparable>
void Heap<Comparable>::deleteMin() {
    if (heapVector.empty() || heapVector.size() == 0 )
        return;

    heapVector[0] = std::move(heapVector.back());
    heapVector.pop_back();
    if (heapVector.empty() || heapVector.size() == 0)
        return;
    percolateDown();
}

template<typename Comparable>
int Heap<Comparable>::size() const {
    return heapVector.size();
}

template<typename Comparable>
const Comparable& Heap<Comparable>::getElement(int index) const {
    return heapVector[index];
}
