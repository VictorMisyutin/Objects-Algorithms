#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "heap.cpp"

using namespace std;
ofstream  fout;            // declare and create an output stream
vector<int>  inputData;       // all keys from the input file

// Print data and heap

void printHeap(const string& description, const Heap<int>& heap) {
    fout << description << "\n";
    // fout << "[" << heap.size() << "] ";
    for (int i = 0; i < heap.size(); ++i) fout << heap.getElement(i) << " ";
    fout << "\n\n";
}

// Consider heap elements ordered if first <= second or second is beyound heap size

bool areHeapElementsOrdered(const Heap<int>& heap, const int i, const int j) {
    return i >= heap.size() || j >= heap.size() || heap.getElement(i) <= heap.getElement(j);
}

// Returns stringized element or "none" if beyond heap size

string heapElement(const Heap<int>& heap, const int i) {
    return i < heap.size() ? to_string(heap.getElement(i)) : "none";
}

// Check that it is really a heap, throw an exceeption otherwise

void checkHeap(const Heap<int>& heap) {
    for (int i = 0; i < heap.size(); ++i) {
        if (areHeapElementsOrdered(heap, i, i * 2 + 1) && areHeapElementsOrdered(heap, i, i * 2 + 2)) continue;

        printHeap("Corrupted", heap);

        fout << "Error: heap violation at index " << i
            << ", heap[" << i << "] = " << heapElement(heap, i)
            << ", heap[" << (i * 2 + 1) << "] = " << heapElement(heap, i * 2 + 1)
            << ", heap[" << (i * 2 + 2) << "] = " << heapElement(heap, i * 2 + 2)
            << "\n";
        throw runtime_error("Not a heap");
    }

}

// Insert one element, check, and print 

void insertOne(Heap<int>& heap, int element) {
    fout << "Insert " << element << "\n";

    heap.insert(element);
    checkHeap(heap);

    printHeap("Heap after insert " + to_string(element), heap);
}

// Delete minimun element, check, and print

void deleteOne(Heap<int>& heap) {
    fout << "Delete " << heap.getElement(0) << "\n";
    heap.deleteMin();
    checkHeap(heap);
}

void testData() {
    Heap<int> heap;
    // check later ----------------
    for (const int& key : inputData) {
        heap.insert(key);
        checkHeap(heap);
    }

    printHeap("Heap", heap);

    while (heap.size() > 0) {
        heap.deleteMin();
        printHeap("Delete min\nHeap after Delete min", heap);
    }
    fout << "Deleted all" << endl;
}


// Read data from the input file into a vector and prepare sorted versions of the vector

void readData(const string& inputFile) {
    ifstream  fin(inputFile);
    int key;
    inputData.clear();

    // fout << "Input data ";
    while (fin >> key) {
        inputData.push_back(key);
        // fout << " " << key;
    }
    fout << "\n";
    fin.close();
}

// Test the input file, print result to the output file

void testFile(const string& inputFile, const string& outputFile) {
    fout.open(outputFile);
    readData(inputFile);
    testData();
    fout.close();

}

// Main program

int main() {
    try {
        for (int i = 1; i <= 4; ++i) {
            string suffix = to_string(i) + ".txt";
            testFile("in" + suffix, "out" + suffix);
        }

    }
    catch (const exception& ex) {
        if (fout) {
            fout << "Exception: " << ex.what() << "\n";
            cout << "Exception: " << ex.what() << "\n";
        }
    }

}

