#include "LinearProbingHash.h"
#include "QuadraticProbingHash.h"
#include "DoubleHashingProbingHash.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const int tableSize = 191;	// hash tables size
const int doubleFactor = 181;	// factor R to be used in double hashing

ofstream	fout;		// declare and create an output stream
ofstream	fout2;		// declare and create an output stream


void testKeyValue(
    string description,
    HashInterface<int, int>& hashTable,
    const int		 key,
    const int		 value
) {
    const int previousCollisions = hashTable.getCollisions();

    hashTable.put(key, value);

    const int* retrievedValue = hashTable.get(key);
    const string& retrievedText = retrievedValue != nullptr ? to_string(*retrievedValue) : "null";

    fout << to_string(key) << " : " << to_string(value) << " -> " << retrievedText << ", collisions " << (hashTable.getCollisions() - previousCollisions) << "\n";

    if (retrievedValue == nullptr || *retrievedValue != value) {
        cout << "Retrieved value " << retrievedText << " does not match stored value " << to_string(value) << " for key " << key << "\n";
        throw runtime_error("value mismatch");
    }
}

void testInputKey(
    const int  	          key,
    LinearProbingHash<int, int>& lph,
    QuadraticProbingHash<int,int>&	  qph,
    DoubleHashingProbingHash<int,int>&	  dhph
)
{
    const int value = key * 2;

    testKeyValue("Linear   ", lph, key, value);
    testKeyValue("Quadratic", qph, key, value);
    testKeyValue("Double   ", dhph, key, value);

    fout << "\n";

}

void testData(
    const string& description,
    vector<int>* data
)
{
    fout << "Format of output\n";
    fout << "key : value->retrievedValue, collisions number Collisions\n";
    fout << "Linear total number Collisions\n";
    fout << "Quadratic total number Collisions\n";
    fout << "Double hashing total number Collisions\n" << endl;


    fout << "*** " << description << " Start *** " << "\n\n";

    LinearProbingHash<int, int>        lph(tableSize);
    QuadraticProbingHash<int,int>     qph  ( tableSize );
    DoubleHashingProbingHash<int, int> dhph ( tableSize, doubleFactor ) ;


    // in the file?
    for (int key : *data) testInputKey(key, lph, qph, dhph);


    fout << "Linear    " << lph.getCollisions() << " collisions\n";
    fout2 << "\n*** Linear Probing " + description + " Start ***\n" << std::endl;
    lph.printTable(fout2);
    fout2 << "*** Linear Probing " + description + " end ***\n\n";


    fout << "Quadratic    " << qph.getCollisions() << " collisions\n";
    fout2 << "\n*** Quadratic Probing " + description + " Start ***\n" << std::endl;
    qph.printTable(fout2);
    fout2 << "*** Quadratic Probing " + description + " end ***\n\n";


    fout << "Double Hashing    " << dhph.getCollisions() << " collisions\n";
    fout2 << "\n*** Double Hashing Probing " + description + " Start ***\n" << std::endl;
    dhph.printTable(fout2);
    fout2 << "*** Double Hashing Probing " + description + " end ***\n\n";

    fout << "\n*** " << description << " End *** " << "\n\n";

}

void readData(
    const string& inputFile,
    vector<int>* data
)
{
    ifstream  fin(inputFile);
    int       key;

    while (fin >> key) data->push_back(key);

    fin.close();
}

void testFile(

    const string& inputFilename,
    const string& outputFilename1,
    const string& outputFilename2
)
{
    cout << "Input file " << inputFilename << ", output file " << outputFilename1 << "\n";

    vector<int>*	data = new vector<int>();		// all keys from the input file
    readData(inputFilename, data);
    fout.open(outputFilename1);
    fout2.open( outputFilename2 );

    // read data

    testData("Random Order", data);

    int i, j;
    bool swapped;
    int dataSize = data->size(); // Get the size of the vector
    for (i = 0; i < dataSize - 1; i++) {
        swapped = false;
        for (j = 0; j < dataSize - i - 1; j++) {
            if ((*data)[j] > (*data)[j + 1]) { // Access elements through the pointer
                swap((*data)[j], (*data)[j + 1]);
                swapped = true;
            }
        }
        if (!swapped)
            break;
    }


    testData("Ascending Order", data);

    std::reverse(data->begin(), data->end());

    testData("Descending Order", data);

    fout.close();
    fout2.close();

    cout << "Done\n";

}

int main() {
    try {
        testFile("in150.txt", "out150_collisions.txt", "out150_tables.txt");
        testFile("in160.txt", "out160_collisions.txt", "out160_tables.txt");
        testFile("in170.txt", "out170_collisions.txt", "out170_tables.txt");
        testFile("in180.txt", "out180_collisions.txt", "out180_tables.txt");
    }
    catch (exception e) {
        cout << "Exception: " << e.what() << "\n";

    }

    return 0;
}


