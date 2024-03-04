// If the generic classes and interfaces seem too complex, just write a code
// that works with concrete classes and int or Integer keys and values.
//
// Some languages do not require to specify variable/function types but you 
// shall specify types (or hints) if possible.
//
// If the language requires it, use int where plain number is enough and use 
// a pointer to int or Integer type where the value can be a number or the null. 
//
// Use const or final instead of constant keyword if the language supports it. Otherwise 
// diregard (omit) it.
//
// & and * in variable definitions are C++ specific hints. Disregard them
// if using other languages.
//
// In value1 EQUAL value2, you must use language specific comparison that compares
// values data, not just references. For example, in the case of Java Integer type,
// value1 == value2 compares two references and so cannot be used.
//
// Some languages do not have null keyword and so you need to replace it appropriately.
// For example, use nullptr in C++.
//
// Some languages have vectors. If not, replace vector with an appropriate array type.
//
// INPUT_STREAM and OUTPUT_STREAM are to be replaced with language specific
// input/output streams. Replace stdout with a stream corresponding the standard
// output (usually your terminal or console).
//
// stream << expression means write the expression value as text to the stream.
// stream >> variable means read from the stream, convert from text, and assign to 
// the variable. Replace << and >> with appropriate language constructs. 
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include "LinearProbingHash.hpp" // Include the appropriate header file for your hash table

using namespace std;

class Driver {
private:
    const int tableSize = 191;
    const int doubleFactor = 181;
    ofstream fout;
    ofstream fout2;
    vector<int> data;

public:
    Driver(const string& filename) : fout(filename) {}

    void testKeyValue(const string& description, HashInterface<int, int>& hashTable, const int key, const int value) {
        const int previousCollisions = hashTable.getCollisions();

        hashTable.put(key, value);

        const int* retrievedValue = hashTable.get(key);
        const string retrievedText = retrievedValue != nullptr ? to_string(*retrievedValue) : "null";

        fout << key << " : " << value << " -> " << retrievedText << ", collisions " << (hashTable.getCollisions() - previousCollisions) << "\n";

        if (retrievedValue == nullptr || !(*retrievedValue == value)) {
            fout << "Retrieved value " << retrievedText << " does not match stored value " << value
                 << " for key " << key << "\n";
            throw runtime_error("value mismatch");
        }
    }

    void testInputKey(const int key, HashInterface<int, int>& lph) {
        const int value = key * 2;

        testKeyValue("Linear   ", lph, key, value);
        fout << "\n";
    }

    void testData(const string& description) {
        fout << "*** " << description << " Start *** " << "\n\n";

        LinearProbingHash<int, int> lph(tableSize);

        for (int key : data) testInputKey(key, lph);

        fout << "Linear    " << lph.getCollisions() << " collisions\n";

        fout << "\n*** " << description << " End *** " << "\n\n";
    }

    void readData(const string& inputFile) {
        ifstream fin(inputFile);
        int key;
        while (fin >> key) data.push_back(key);
        fin.close();
    }

    void testFile(const string& inputFilename, const string& outputFilename1, const string& outputFilename2) {
        cout << "Input file " << inputFilename << ", output files " << outputFilename1 << " and " << outputFilename2 << "\n";

        readData(inputFilename);
        fout.open(outputFilename1);
        fout2.open(outputFilename2);

        testData("Random Order");

        sort(data.begin(), data.end()); // Sort in ascending order
        testData("Ascending Order");

        reverse(data.begin(), data.end()); // Sort in descending order
        testData("Descending Order");

        fout.close();
        fout2.close();

        cout << "Done\n";
    }
};

int main() {
    Driver driver("output.txt");
    driver.testFile("in150.txt", "collisions.txt", "tables.txt");
    return 0;
}
