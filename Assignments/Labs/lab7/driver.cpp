#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <boost/multiprecision/cpp_int.hpp>

using namespace std;
using namespace boost::multiprecision;

void GetPQEValues(string fileName, cpp_int* P, cpp_int* Q, cpp_int* E) {
    ifstream file(fileName);
    string fileContents;

    if (file.is_open()) {
        char c;
        while (file.get(c)) {
            if (c != ' ' && c != '\n') {
                fileContents += c;
            }
        }
        file.close();
    }
    else {
        cout << "Unable to open file." << endl;
        return;
    }

    vector<pair<char, string>> letterNumberPairs;

    char lastNonDigit = '\0';
    string currentNumber;

    for (char c : fileContents) {
        if (isdigit(c)) {
            currentNumber += c;
        }
        else {
            if (!currentNumber.empty()) {
                letterNumberPairs.push_back(make_pair(lastNonDigit, currentNumber));
                currentNumber.clear();
            }
            lastNonDigit = c;
        }
    }
    letterNumberPairs.push_back(make_pair(lastNonDigit, currentNumber));

    for (const auto& pair : letterNumberPairs) {
        if (pair.first == 'p') {
            *P = cpp_int(pair.second);
        }
        else if (pair.first == 'q') {
            *Q = cpp_int(pair.second);
        }
        else if (pair.first == 'e') {
            *E = cpp_int(pair.second);
        }
    }
}

cpp_int mod_inverse(cpp_int a, cpp_int m) {
    cpp_int m0 = m;
    cpp_int y = 0, x = 1;
    if (m == 1)
        return 0;
    while (a > 1) {
        cpp_int q = a / m;
        cpp_int t = m;
        m = a % m, a = t;
        t = y;
        y = x - q * y;
        x = t;
    }
    if (x < 0)
        x += m0;
    return x;
}

cpp_int rsa_encrypt(cpp_int plaintext, cpp_int E, cpp_int N) {
    return powm(plaintext, E, N); // Using powm for modular exponentiation
}

int calculate_block_length(const cpp_int& N) {
    cpp_int block_size = 0xFF; // Start with a block size of 1 byte (0xFF)
    cpp_int value = 1; // Initialize value to 1 byte
    int block_length = 0;

    while (value < N) {
        value *= block_size; // Increase block size by 1 byte (0xFF)
        block_length++;
    }

    return block_length;
}

int main() {
    for (int a = 0; a < 4;a++) {
        cpp_int P;
        cpp_int Q;
        cpp_int E;
        GetPQEValues(to_string(a) + "_keymat.txt", &P, &Q, &E);
        cpp_int N = P * Q;
        cpp_int phi_N = (P - 1) * (Q - 1);
        cpp_int D = mod_inverse(E, phi_N);
        ofstream debugFile(to_string(a) + "_debug.txt");

        debugFile << "--- RSAAlgorithm" << endl;
        debugFile << "p " << to_string(P) << endl;
        debugFile << "q " << to_string(Q) << endl;
        debugFile << "e " << to_string(E) << endl;
        debugFile << "n " << to_string(N) << endl;
        debugFile << "d " << to_string(D) << endl;

        // read data from file


        ifstream inFile(to_string(a) + "_in.dat", ios::binary);
        stringstream buffer;
        buffer << inFile.rdbuf();
        string plaintext = buffer.str();
        inFile.close();

        debugFile << "*** Encrypting " << to_string(a) << "_in.dat, size 1 -> " << to_string(a) << "_encrypted.txt ***" << endl;

        vector<cpp_int> plaintextNumbers;
        for (char c : plaintext) {
            plaintextNumbers.push_back(static_cast<cpp_int>(c));
        }
        cpp_int plaintextNumber = 0;
        for (cpp_int num : plaintextNumbers) {
            plaintextNumber = plaintextNumber * 256 + num; // Shift by 8 bits (multiply by 256) and add the next ASCII value
        }
        cpp_int ciphertextNumber = rsa_encrypt(plaintextNumber, E, N);

        stringstream hexStream;
        hexStream << hex << ciphertextNumber;
        string hexCiphertext = hexStream.str();

        ofstream encryptedFile(to_string(a) + "_encrypted.txt");
        int block_length = calculate_block_length(N);
        encryptedFile << hexCiphertext << endl;
        encryptedFile << block_length;
        encryptedFile.close();
        debugFile << "*** Decrypting " << to_string(a) << "_in.dat, size 1 -> " << to_string(a) << "_decrypted.txt ***" << endl;

    }
    return 0;
}