#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <bits/stdc++.h>

using namespace std;

int hash_function(int key) {
    // return key;
    unsigned int result = (key >> 8) | ((key & 0xFF) << 16);
    return result;
}

void linear_probing_insert(vector<pair<int, int>>& table, int key, int value, int& collisions, ofstream& outputFile) {
int index = hash_function(key);
index = index % table.size();
while (table[index].first != -1) {
    index = (index + 1) % table.size();
    collisions++;
}
table[index] = make_pair(key, value);
outputFile << key << " : " << value << " -> " << value << ", collisions: " << collisions << endl;
}

void quadratic_probing_insert(vector<pair<int, int>>& table, int key, int value, int& collisions, ofstream& outputFile) {
int startingHash = hash_function(key);
startingHash = startingHash % table.size();
int index = startingHash;
int i = 1;
while (table[index].first != -1) {
    index = (startingHash + i * i) % table.size(); 
    i++;
    collisions++;
}
table[index] = make_pair(key, value);
outputFile << key << " : " << value << " -> " << value << ", collisions: " << collisions << endl;
}

int double_factor(int key) {
int doubleFactor = 181;
return doubleFactor - (key % doubleFactor);
}

void double_hashing_insert(vector<pair<int, int>>& table, int key, int value, int& collisions, ofstream& outputFile) {
int startingHash = hash_function(key);
startingHash = startingHash % table.size();
int index = startingHash;
int step = double_factor(key);
int count = 1;
while (table[index].first != -1) {
    index = (startingHash + count*step) % table.size(); 
    collisions++;
    count++;
}
table[index] = make_pair(key, value);
outputFile << key << " : " << value << " -> " << value << ", collisions: " << collisions << endl;
}

void printTable(const vector<pair<int, int>>& table, ofstream& outputFile) {
outputFile << "print table.size()=" << table.size() << endl;
for (int i = 0 ; i < table.size(); i++) {
    if (table[i].first != -1) {
        outputFile << "index=" << i << " key=" << table[i].first << " value=" << table[i].second << endl;
    } 
}  
}

struct ProcessResult {
vector<int> collisions;
vector<pair<int, int>> hash_tables[3];
};

ProcessResult processNumbers(const vector<int>& numbers, ofstream& outputFile) {
int table_size = 191;

ProcessResult result;
result.collisions.resize(3);
result.collisions[0] = 0;
result.collisions[1] = 0;
result.collisions[2] = 0;

for (int i = 0; i < 3; ++i) {
    result.hash_tables[i].resize(table_size, make_pair(-1, -1));
}

outputFile << "Linear Probing" << endl;
for (int num : numbers) {
    int key = num;
    int value = 2 * num;
    linear_probing_insert(result.hash_tables[0], key, value, result.collisions[0], outputFile);
}

outputFile << "\nQuadratic Probing" << endl;

for (int num : numbers) {
    int key = num;
    int value = 2 * num;
    quadratic_probing_insert(result.hash_tables[1], key, value, result.collisions[1], outputFile);
}

outputFile << "\nDouble Hashing Probing" << endl;

for (int num : numbers) {
    int key = num;
    int value = 2 * num;
    double_hashing_insert(result.hash_tables[2], key, value, result.collisions[2], outputFile);
}

outputFile << endl;

outputFile << "Linear: " << result.collisions[0] << " collisions" << endl;
outputFile << "Quadratic: " << result.collisions[1] << " collisions" << endl;
outputFile << "Double: " << result.collisions[2] << " collisions" << endl;

return result;
}

int main() {
for(int i = 5; i < 9; i++) {
    ifstream file("in1" + to_string(i) + "0.txt");
    vector<int> numbers;
    int num;
    int size = 0;
    while (file >> num) {
        numbers.push_back(num);
        size++;
    }
    file.close();

    ofstream collisionFile("out1" + to_string(i) + "0_collisions.txt");
    ofstream tableFile("out1" + to_string(i) + "0_tables.txt");

    // random order

        // collision file
    collisionFile << "*** Random Order Start ***\n" << endl;
    ProcessResult randomResult = processNumbers(numbers, collisionFile);
    vector<pair<int, int>>* hash_tables_random = &randomResult.hash_tables[0];
    collisionFile << "\n*** Random Order End ***" << endl;

        // table file

            // Linear probing
    tableFile << "*** Linear probing Random Order Start ***\n" << endl;
    printTable(hash_tables_random[0], tableFile);
    tableFile << "\nLinear probing " << randomResult.collisions[0] << " collisions" <<endl;
    tableFile << "\n*** Linear probing Random Order End ***\n" << endl;
            
            // Quadratic probing
    tableFile << "*** Quadratic probing Random Order Start ***\n" << endl;
    printTable(hash_tables_random[1], tableFile);
    tableFile << "\nQuadratic probing " << randomResult.collisions[1] << " collisions" <<endl;
    tableFile << "\n*** Quadratic probing Random Order End ***\n" << endl;

            // Double Hashing probing
    tableFile << "*** Double Hashing  probing Random Order Start ***\n" << endl;
    printTable(hash_tables_random[2], tableFile);
    tableFile << "\nDouble Hashing probing " << randomResult.collisions[2] << " collisions" <<endl;
    tableFile << "\n*** Double Hashing probing Random Order End ***\n" << endl;

    // delete[] randomResult.hash_tables;


    // ascending order
    
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) 
            if (numbers[j] > numbers[j + 1]) 
                swap(numbers[j], numbers[j + 1]);
    }
        // collision file
    collisionFile << "*** Ascending Order Start ***\n" << endl;
    ProcessResult ascResult = processNumbers(numbers, collisionFile);
    vector<pair<int, int>>* hash_tables_asc = &ascResult.hash_tables[0];
    collisionFile << "\n*** Ascending Order End ***" << endl;

        // table file
        
            // Linear probing
    tableFile << "*** Linear probing Ascending Order Start ***\n" << endl;
    printTable(hash_tables_asc[0], tableFile);
    tableFile << "\nLinear probing " << ascResult.collisions[0] << " collisions" <<endl;
    tableFile << "\n*** Linear probing Ascending Order End ***\n" << endl;
            
            // Quadratic probing
    tableFile << "*** Quadratic probing Ascending Order Start ***\n" << endl;
    printTable(hash_tables_asc[1], tableFile);
    tableFile << "\nQuadratic probing " << ascResult.collisions[1] << " collisions" <<endl;
    tableFile << "\n*** Quadratic probing Ascending Order End ***\n" << endl;

            // Double Hashing probing
    tableFile << "*** Double Hashing  probing Ascending Order Start ***\n" << endl;
    printTable(hash_tables_asc[2], tableFile);
    tableFile << "\nDouble Hashing probing " << ascResult.collisions[2] << " collisions" <<endl;
    tableFile << "\n*** Double Hashing probing Ascending Order End ***\n" << endl;

    // delete[] ascResult.hash_tables;


    // descending order
    std::reverse(numbers.begin(), numbers.end());    
        // collision file

    collisionFile << "*** Descending Order Start ***\n" << endl;
    ProcessResult descResult = processNumbers(numbers, collisionFile);
    vector<pair<int, int>>* hash_tables_desc = &descResult.hash_tables[0];
    collisionFile << "\n*** Descending Order End ***" << endl;

        // table file
        
            // Linear probing
    tableFile << "*** Linear probing Descending Order Start ***\n" << endl;
    printTable(hash_tables_desc[0], tableFile);
    tableFile << "\nLienar probing " << descResult.collisions[0] << " collisions" <<endl;
    tableFile << "\n*** Linear probing Descending Order End ***\n" << endl;
            
            // Quadratic probing
    tableFile << "*** Quadratic probing Descending Order Start ***\n" << endl;
    printTable(hash_tables_desc[1], tableFile);
    tableFile << "\nQuadratic probing " << descResult.collisions[1] << " collisions" <<endl;
    tableFile << "\n*** Quadratic probing Descending Order End ***\n" << endl;

            // Double Hashing probing
    tableFile << "*** Double Hashing  probing Descending Order Start ***\n" << endl;
    printTable(hash_tables_desc[2], tableFile);
    tableFile << "\nDouble Hashing probing " << descResult.collisions[2] << " collisions" <<endl;
    tableFile << "\n*** Double Hashing probing Descending Order End ***\n" << endl;

    // delete[] descResult.hash_tables;

    collisionFile.close();
}

return 0;
}
