#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip> // for setw and setfill
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
    cpp_int block_size = 0xFF;
    cpp_int value = 1;
    int block_length = -1;

    while (value < N) {
        value *= block_size;
        block_length++;
    }
    return block_length;
}

int main() {
    for (int a = 0; a < 4; a++) {
        cpp_int P;
        cpp_int Q;
        cpp_int E;
        GetPQEValues(to_string(a) + "_keymat.txt", &P, &Q, &E);
        cpp_int N = P * Q;
        cpp_int phi_N = (P - 1) * (Q - 1);
        cpp_int D = mod_inverse(E, phi_N);
        ofstream debugFile(to_string(a) + "_debug.txt");
        int block_length = calculate_block_length(N);

        debugFile << "--- RSAAlgorithm" << endl;
        debugFile << "p " << to_string(P) << endl;
        debugFile << "q " << to_string(Q) << endl;
        debugFile << "e " << to_string(E) << endl;
        debugFile << "n " << to_string(N) << endl;
        debugFile << "d " << to_string(D) << endl;

        // Read data from file
        ifstream inFile(to_string(a) + "_in.dat");
        ostringstream buffer;
        if (inFile.peek() == '\xEF') {
            inFile.get();
            if (inFile.get() != '\xBB' || inFile.get() != '\xBF') {
                // Invalid BOM, handle error or reset the stream
                // inFile.seekg(0); // Reset the stream position if needed
            }
        }
        buffer << inFile.rdbuf();
        string plaintext = buffer.str();
        inFile.close();
        cout << plaintext << "===================" << endl;
        debugFile << "*** Encrypting " << to_string(a) << "_in.dat, block length: " << block_length << " -> " << to_string(a) << "_encrypted.txt ***" << endl;
        ofstream encryptedFile(to_string(a) + "_encrypted.txt");
        encryptedFile.flush();
        for (size_t i = 0; i < plaintext.size(); i += block_length) {
            string block = plaintext.substr(i, block_length);
            cpp_int plaintextNumber = 0;
            debugFile << "BlockReader::readData - Requested count "<< block_length << " bytes, got" << endl;
            int count = 0;
            for (char c : block) {
                if (c == '\n') {
                    debugFile << "[" << count << "] '\\r' ";
                    plaintextNumber = plaintextNumber * 256 + static_cast<unsigned char>('\r');
                    count++;
                    debugFile << "[" << count << "] '\\n' ";
                    plaintextNumber = plaintextNumber * 256 + static_cast<unsigned char>('\n');
                }
                else{
                    debugFile << "[" << count << "] '" << c << "' ";
                    plaintextNumber = plaintextNumber * 256 + static_cast<unsigned char>(c);
                }
                count++;
            }
            debugFile << endl;
            cpp_int ciphertextNumber = rsa_encrypt(plaintextNumber, E, N);

            encryptedFile << hex << block_length << " " << ciphertextNumber << endl;
        }
        encryptedFile.close();
        debugFile << "*** Decrypting " << to_string(a) << "_in.dat, block length: " << block_length << " -> " << to_string(a) << "_decrypted.txt ***" << endl;

    }
    return 0;
}
