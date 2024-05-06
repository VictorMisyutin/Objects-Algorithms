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
#include <string>
#include "LinearProbingHash.h"
using namespace std;

const int tableSize    = 191;	// hash tables size
const int doubleFactor = 181;	// factor R to be used in double hashing

ofstream	fout;		// declare and create an output stream
vector<int>	data;		// all keys from the input file

void testKeyValue ( 
    string&				 description,
    LinearProbingHash<int,int>&	 hashTable,
    const int		 key,
    const int		 value	
){
    const int previousCollisions = hashTable.getCollisions();

    hashTable.put(key,value);

    const int*  retrievedValue = hashTable.get(key);
    const string&   retrievedText  = retrievedValue != nullptr ? to_string(*retrievedValue) : "null";

    fout << to_string(key) << " : " << to_string(value) << " -> " << retrievedText   
                    << ", collisions " << (hashTable.getCollisions()-previousCollisions) << "\n";
    
    if ( retrievedValue == nullptr || ! ( *retrievedValue == value )  ) 
        fout << "Retrieved value " << retrievedText << " does not match stored value " << to_string(value) << " for key " << key << "\n";
        throw runtime_error("value mismatch");
}

void testInputKey (
    const int  	          key,
    LinearProbingHash<int,int>&	  lph
    // QuadraticProbingHash<int,int>&	  qph,
    // DoubleHashingProbingHash<int,int>&	  dhph
)	
{
    const int value = key*2;
    
    testKeyValue( "Linear   ", lph,  key, value );
    testKeyValue( "Quadratic", qph,  key, value );
    testKeyValue( "Double   ", dhph, key, value );

    fout << "\n";

}

void testData (
    const string& description
)
{
    fout << "*** " << description << " Start *** " << "\n\n";

    LinearProbingHash<int,int>        lph  ( tableSize );
    // QuadraticProbingHash<Integer,Integer>     qph  ( tableSize );
    // DoubleHashingProbingHash<Integer,Integer> dhph ( tableSize, doubleFactor ) ;

    // in the file?
    for (int key : data ) testInputKey(key,lph,qph,dhph);

    fout << "Linear    " << lph.getCollisions()  << " collisions\n"
            lph.printTable();

    // fout << "Quadratic " << qph.getCollisions()  << " collisions\n"
    //         qph.printTable();

    // fout << "Double    " << dhph.getCollisions() << " collisions\n"
    //         dhph.printTable();

    fout << "\n*** " << description << " End *** " << "\n\n";

}
    
void readData  ( 
    const string&  inputFile
)
{
    ifstream  fin(inputFile);		
    int       key;

    while ( fin >> key ) data.push_back(key);

    fin.close();
}

void testFile (

    const string&	inputFilename,
    const string&	outputFilename1,
    const string&	outputFilename2
)
{
    cout << "Input file " << inputFilename << ", output file " << outputFilename << "\n";

    readData ( inputFilename  );
    fout.open( outputFilename1 );
    // fout2.open( outputFilename2 );

    // read data
    testData( "Random Order" );

    for (int i = 0; i < tableSize - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) 
            if (data[j] > data[j + 1]) 
                swap(data[j], data[j + 1]);
    }
    testData( "Ascending Order" );

    std::reverse(data.begin(), data.end());    

    testData( "Descending Order" );

    fout.close();

    cout << "Done\n";

}

int main(){
    try{
        testFile( "in150.txt", "out150_collisions.txt","out150_tables.txt" );
        testFile( "in160.txt", "out160_collisions.txt","out160_tables.txt" );
        testFile( "in170.txt", "out170_collisions.txt","out170_tables.txt" );
        testFile( "in180.txt", "out180_collisions.txt","out180_tables.txt" );
    }
    catch (exception e){
        cout << "Exception: " << e.what() << "\n";

    }

    return 0;
}

				
		