#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int hashFunction(int key) {
    return 2*key;
}

void linear_probing_insert(vector<pair<int, int>>& table, int key, int value, int& collisions, ofstream& outputFile) {
<<<<<<< HEAD
    int index = hash_function(key);
    index = index % table.size();
=======
    int index = hashFunction(key);
>>>>>>> 9b123213076b75f5131d251c3f5d9243ee049732
    while (table[index].first != -1) {
        index = (index + 1) % table.size();
        collisions++;
    }
    table[index] = make_pair(key, value);
    outputFile << key << " : " << value << " -> " << value << ", collisions: " << collisions << endl;
}

<<<<<<< HEAD
void quadratic_probing_insert(vector<pair<int, int>>& table, int key, int value, int& collisions, ofstream& outputFile) {
    int index = hash_function(key);
    index = index % table.size();
=======
void quadraticProbingInsert(vector<pair<int, int>>& table, int key, int value, int& collisions, ofstream& outputFile) {
    int index = hashFunction(key);
>>>>>>> 9b123213076b75f5131d251c3f5d9243ee049732
    int i = 1;
    while (table[index].first != -1) {
        index = (index + i * i) % table.size(); 
        i++;
        collisions++;
    }
    table[index] = make_pair(key, value);
    outputFile << key << " : " << value << " -> " << value << ", collisions: " << collisions << endl;
}

int doubleFactor(int key) {
    int doubleFactor = 7;
    return doubleFactor - (key % doubleFactor);
}

<<<<<<< HEAD
void double_hashing_insert(vector<pair<int, int>>& table, int key, int value, int& collisions, ofstream& outputFile) {
    int index = hash_function(key);
    index = index % table.size();
    int step = double_factor(key);
=======
void doubleHashingInsert(vector<pair<int, int>>& table, int key, int value, int& collisions, ofstream& outputFile) {
    int index = hashFunction(key);
    int step = doubleFactor(key);
>>>>>>> 9b123213076b75f5131d251c3f5d9243ee049732
    while (table[index].first != -1) {
        index = (index + step) % table.size(); 
        collisions++;
    }
    table[index] = make_pair(key, value);
    outputFile << key << " : " << value << " -> " << value << ", collisions: " << collisions << endl;
}

void printTable(const vector<pair<int, int>>& table, ofstream& outputFile) {
    int count = 0;
    outputFile << "print table.size()=" << table.size() << endl;
    for (const auto& entry : table) {
        if (entry.first != -1) {
            outputFile << "index=" << count << " key=" << entry.first << " value=" << entry.second << endl;
            count++;
        } 
    }  
}

struct ProcessResult {
    vector<int> collisions;
    vector<pair<int, int>> hash_tables[3];
};

ProcessResult processNumbers(const vector<int>& numbers, ofstream& outputFile) {
    int table_size = 11;

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
        quadraticProbingInsert(result.hash_tables[1], key, value, result.collisions[1], outputFile);
    }

    outputFile << "\nDouble Hashing Probing" << endl;

    for (int num : numbers) {
        int key = num;
        int value = 2 * num;
        doubleHashingInsert(result.hash_tables[2], key, value, result.collisions[2], outputFile);
    }

    outputFile << endl;

    outputFile << "Linear: " << result.collisions[0] << "collisions" << endl;
    outputFile << "Quadratic: " << result.collisions[1] << "collisions" << endl;
    outputFile << "Double: " << result.collisions[2] << "collisions" << endl;

    return result;
}

int main() {
    for(int i = 1; i < 6; i++) {
        ifstream file("in" + to_string(i) + ".txt");
        vector<int> numbers;
        int num;
        while (file >> num) {
            numbers.push_back(num);
        }
        file.close();

        ofstream collisionFile("out" + to_string(i) + "_collisions.txt");
        ofstream tableFile("out" + to_string(i) + "_tables.txt");

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
        
            // collision file
        collisionFile << "*** Ascending Order Start ***\n" << endl;
        sort(numbers.begin(), numbers.end());
        ProcessResult ascResult = processNumbers(numbers, collisionFile);
        vector<pair<int, int>>* hash_tables_asc = &randomResult.hash_tables[0];
        collisionFile << "\n*** Ascending Order End ***" << endl;

            // table file
            
                // Linear probing
        tableFile << "*** Linear probing Random Order Start ***\n" << endl;
        printTable(hash_tables_asc[0], tableFile);
        tableFile << "\nLinear probing " << ascResult.collisions[0] << " collisions" <<endl;
        tableFile << "\n*** Linear probing Random Order End ***\n" << endl;
                
                // Quadratic probing
        tableFile << "*** Quadratic probing Random Order Start ***\n" << endl;
        printTable(hash_tables_asc[1], tableFile);
        tableFile << "\nQuadratic probing " << ascResult.collisions[1] << " collisions" <<endl;
        tableFile << "\n*** Quadratic probing Random Order End ***\n" << endl;

                // Double Hashing probing
        tableFile << "*** Double Hashing  probing Random Order Start ***\n" << endl;
        printTable(hash_tables_asc[2], tableFile);
        tableFile << "\nDouble Hashing probing " << ascResult.collisions[2] << " collisions" <<endl;
        tableFile << "\n*** Double Hashing probing Random Order End ***\n" << endl;

        // delete[] ascResult.hash_tables;


        // descending order
            // collision file
        collisionFile << "*** Descending Order Start ***\n" << endl;
        reverse(numbers.begin(), numbers.end());
        ProcessResult descResult = processNumbers(numbers, collisionFile);
        vector<pair<int, int>>* hash_tables_desc = &randomResult.hash_tables[0];
        collisionFile << "\n*** Descending Order End ***" << endl;

            // table file
            
                // Linear probing
        tableFile << "*** Linear probing Random Order Start ***\n" << endl;
        printTable(hash_tables_desc[0], tableFile);
        tableFile << "\nLienar probing " << descResult.collisions[0] << " collisions" <<endl;
        tableFile << "\n*** Linear probing Random Order End ***\n" << endl;
                
                // Quadratic probing
        tableFile << "*** Quadratic probing Random Order Start ***\n" << endl;
        printTable(hash_tables_desc[1], tableFile);
        tableFile << "\nQuadratic probing " << descResult.collisions[1] << " collisions" <<endl;
        tableFile << "\n*** Quadratic probing Random Order End ***\n" << endl;

                // Double Hashing probing
        tableFile << "*** Double Hashing  probing Random Order Start ***\n" << endl;
        printTable(hash_tables_desc[2], tableFile);
        tableFile << "\nDouble Hashing probing " << descResult.collisions[2] << " collisions" <<endl;
        tableFile << "\n*** Double Hashing probing Random Order End ***\n" << endl;

        // delete[] descResult.hash_tables;

        collisionFile.close();
    }

    return 0;
}
