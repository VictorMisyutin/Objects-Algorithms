#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <locale>
#include <codecvt>
#include <io.h>
#include <fcntl.h>
#include <boost/multiprecision/cpp_int.hpp>

#include "FileComparator.cpp"

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

string decryptRSA(const string& ciphertext, const cpp_int& N, const cpp_int& D, ofstream& df, int& length) {
    // Convert ciphertext from hexadecimal to decimal
    istringstream iss(ciphertext);
    cpp_int c_dec;
    iss >> hex >> c_dec;

    // Perform modular exponentiation to decrypt the ciphertext
    cpp_int plaintext = powm(c_dec, D, N);

    // Convert plaintext from cpp_int to string
    ostringstream oss;
    oss << hex << plaintext;
    string plaintext_hex = oss.str();
    df << "RSAAlgorithm::decrypt 0x" << hex << uppercase << ciphertext << "-> 0x" << plaintext_hex << "\n" << endl;
    df << "BlockWriter::writeData - Writing " << plaintext_hex << " as "  << length << " bytes\n" << endl;

    // Convert hexadecimal plaintext to ASCII
    string plaintext_ascii;
    int count = 0;
    for (size_t i = 0; i < plaintext_hex.length(); i += 2) {
        string byte = plaintext_hex.substr(i, 2);
        char chr = static_cast<char>(stoi(byte, nullptr, 16));
        if (chr == '\r') {
            df << "[" << count << "] '\\r'";
        }
        else if (chr == '\n') {
            df << "[" << count << "] '\\n'";
            plaintext_ascii.push_back(chr);
        }
        else {
            df << "[" << count << "] '" << chr << "'";
            plaintext_ascii.push_back(chr);
        }
    }
    df << "\n" << endl;

    return plaintext_ascii;
}

bool compareFiles(const string& p1, const string& p2) {
    ifstream f1(p1, ifstream::binary | ifstream::ate);
    ifstream f2(p2, ifstream::binary | ifstream::ate);

    if (f1.fail() || f2.fail()) {
        cout << "first fail";
        return false;
    }

    f1.seekg(0, ifstream::beg);
    f2.seekg(0, ifstream::beg);
    bool result = equal(istreambuf_iterator<char>(f1.rdbuf()),
        istreambuf_iterator<char>(),
        istreambuf_iterator<char>(f2.rdbuf()));
    return result;
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
        buffer << inFile.rdbuf();
        string plaintext = buffer.str();
        inFile.close();
        debugFile << "\n*** Encrypting " << to_string(a) << "_in.dat, block length: " << block_length << " -> " << to_string(a) << "_encrypted.txt ***\n" << endl;
        ofstream encryptedFile(to_string(a) + "_encrypted.txt");
        encryptedFile.flush();
        vector<string> blocks;
        size_t pos = 0;
        for (int i = 0; i < plaintext.size(); i++) {
            if (plaintext[i] == '\n') {
                plaintext.erase(i, 1);
                plaintext.insert(i, "\r\n");
                i++;
            }
        }
        while (pos < plaintext.size()) {
            string block = plaintext.substr(pos, block_length);
            pos += block_length ;
            blocks.push_back(block);
        }

        // Encrypt each block
        int blockCount = 0;
        for (const string& block : blocks) {
            cpp_int plaintextNumber = 0;
            // Convert characters to numbers
            debugFile << "--- RSACodec::encryptStream block #" << dec << blockCount << ", max length " << dec << block_length << " --- \n" << endl;
            debugFile << "BlockReader::readData - Requested count " << dec << block_length << " bytes, got" << endl;
            int count = 0;
            for (char c : block) {
                if (c == '\r') {
                    debugFile << "[" << count << "] '\\r' ";
                    plaintextNumber = plaintextNumber * 256 + static_cast<unsigned char>('\r');
                }
                else if (c == '\n') {
                    debugFile << "[" << count << "] '\\n' ";
                    plaintextNumber = plaintextNumber * 256 + static_cast<unsigned char>('\n');
                }
                else {
                    debugFile << "[" << count << "] '" << c << "' ";
                    plaintextNumber = plaintextNumber * 256 + static_cast<unsigned char>(c);
                }
                count++;
            }
            // Encrypt the block and write to encrypted file
            cpp_int ciphertextNumber = rsa_encrypt(plaintextNumber, E, N);
            if (count == block_length) {
                debugFile << endl << "BlockReader::readData - Read 0x" << hex << uppercase << plaintextNumber << " as " << dec << block_length << " bytes\n" << endl;
                encryptedFile << hex << uppercase << block_length << " " << ciphertextNumber << endl;
            }
            else {
                debugFile << endl << "BlockReader::readData - Read 0x" << hex << uppercase << plaintextNumber << " as " << dec << count << " bytes\n" << endl;
                encryptedFile << hex << uppercase << count << " " << ciphertextNumber << endl;
            }
            debugFile << "RSAAlgorithm::decrypt 0x" << hex << uppercase << plaintextNumber << " -> 0x" << hex << uppercase << ciphertextNumber << "\n" << endl;
            blockCount++;
        }
        encryptedFile.close();
        // size is the sum of bytes, count number of lines * block_length + count_of_last
        debugFile << "*** Decrypting " << to_string(a) << "_in.dat, block length: " << block_length << " -> " << to_string(a) << "_decrypted.txt ***\n " << endl;

        ifstream ciphertextFile(to_string(a) + "_encrypted.txt");
        ofstream decryptedFile(to_string(a) + "_decrypted.dat");

        string ciphertext;
        int lineCount = 1;
        int length = 0;
        while (getline(ciphertextFile, ciphertext)) {
            unsigned int x;
            stringstream ss;
            ss << dec << ciphertext.substr(0, ciphertext.find(' '));
            ss >> length;
            ciphertext = ciphertext.substr(ciphertext.find(' '), ciphertext.size());
            debugFile << "--- RSACodec::decryptStream block #" << lineCount << ", length " << length << " --- " << endl;
            string plaintext = decryptRSA(ciphertext, N, D, debugFile, length);
            decryptedFile << plaintext;
            lineCount++;
        }
        ciphertextFile.close();
        decryptedFile.close();
        if (compareFiles(to_string(a) + "_in.dat", to_string(a) + "_decrypted.dat")) {
            cout << to_string(a) << " the same " << endl;
        }
        else {
            cout << to_string(a) << " different" << endl;
        }
        
    }
    return 0;
}
// #include <string>
// #include <iostream>
// #include <fcntl.h>
// #include <io.h>
// #include <fstream>
// #include <uchar.h>
// #include <stdio.h>
// #include <sstream>
// #include <vector>
// #include <codecvt>
// #include <boost/multiprecision/cpp_int.hpp>

// using namespace std;
// using namespace boost::multiprecision;

// void GetPQEValues(string fileName, cpp_int* P, cpp_int* Q, cpp_int* E) {
//     ifstream file(fileName);
//     string fileContents;

//     if (file.is_open()) {
//         char c;
//         while (file.get(c)) {
//             if (c != ' ' && c != '\n') {
//                 fileContents += c;
//             }
//         }
//         file.close();
//     }
//     else {
//         return;
//     }

//     vector<pair<char, string>> letterNumberPairs;

//     char lastNonDigit = '\0';
//     string currentNumber;

//     for (char c : fileContents) {
//         if (isdigit(c)) {
//             currentNumber += c;
//         }
//         else {
//             if (!currentNumber.empty()) {
//                 letterNumberPairs.push_back(make_pair(lastNonDigit, currentNumber));
//                 currentNumber.clear();
//             }
//             lastNonDigit = c;
//         }
//     }
//     letterNumberPairs.push_back(make_pair(lastNonDigit, currentNumber));

//     for (const auto& pair : letterNumberPairs) {
//         if (pair.first == 'p') {
//             *P = cpp_int(pair.second);
//         }
//         else if (pair.first == 'q') {
//             *Q = cpp_int(pair.second);
//         }
//         else if (pair.first == 'e') {
//             *E = cpp_int(pair.second);
//         }
//     }
// }

// cpp_int mod_inverse(cpp_int a, cpp_int m) {
//     cpp_int m0 = m;
//     cpp_int y = 0, x = 1;
//     if (m == 1)
//         return 0;
//     while (a > 1) {
//         cpp_int q = a / m;
//         cpp_int t = m;
//         m = a % m, a = t;
//         t = y;
//         y = x - q * y;
//         x = t;
//     }
//     if (x < 0)
//         x += m0;
//     return x;
// }

// cpp_int rsa_encrypt(cpp_int plaintext, cpp_int E, cpp_int N) {
//     return powm(plaintext, E, N);
// }


// int calculate_block_length(const cpp_int& N) {
//     cpp_int block_size = 0xFF;
//     cpp_int value = 1;
//     int block_length = -1;

//     while (value < N) {
//         value *= block_size;
//         block_length++;
//     }
//     return block_length;
// }
// wstring decryptRSA(const wstring& ciphertext, const cpp_int& N, const cpp_int& D, wofstream& df, int& length) {
//     // Convert ciphertext from hexadecimal to decimal
//     string hexStr(ciphertext.begin(), ciphertext.end()); // Convert wstring to string
//     stringstream ss;
//     ss << hex << hexStr;
//     cpp_int c_dec;
//     ss >> c_dec;

//     // Perform modular exponentiation to decrypt the ciphertext
//     cpp_int plaintext = powm(c_dec, D, N);
//     // Convert plaintext from cpp_int to hexadecimal string
//     ss.str(""); // Clear stringstream
//     ss.clear(); // Clear any error flags
//     ss << hex << plaintext;
//     hexStr = ss.str();

//     // Convert hexadecimal string to wstring
//     wstring hexWStr = wstring(hexStr.begin(),hexStr.end());

//     // Display the hexadecimal representation using wcout
//     // Convert plaintext from cpp_int to wstring (ASCII)
//     return hexWStr;
// }

// int main()
// {
//     int FILENUM = 2;
//     _setmode(_fileno(stdout), _O_U16TEXT);

//     cpp_int P;
//     cpp_int Q;
//     cpp_int E;
//     GetPQEValues(to_string(FILENUM) + "_keymat.txt", &P, &Q, &E);
//     cpp_int N = P * Q;
//     cpp_int phi_N = (P - 1) * (Q - 1);
//     cpp_int D = mod_inverse(E, phi_N);
//     int block_length = calculate_block_length(N);
//     wifstream inFile(to_string(FILENUM) + "_in.dat", ios::binary);
//     wofstream debugFile(to_string(FILENUM) + "_debug.txt");
//     wofstream encryptFile(to_string(FILENUM) + "_encrypted.txt");
//     stringstream tempBuffer;
//     tempBuffer << "q " << P.str() << "\ne " << Q.str() << "\ne " << E.str() << "\nn " << N.str() << "\nd " << D.str() << endl;
//     string tempStr = tempBuffer.str();
//     tempBuffer.str("");
//     tempBuffer.clear(); // Clear state flags.
//     debugFile << L"--- RSAAlgorithm" << endl;
//     debugFile << "P " << wstring(tempStr.begin(), tempStr.end()) << endl;

//     wstringstream wss;
//     wss << inFile.rdbuf();
//     wstring fileText = wss.str();
//     wstring temp = fileText.substr(0, 3);

//     // check if has unicode
//     if (temp == L"ï»¿") {
//         // replace weird characters at start
//         fileText.replace(0, 3, L"");
//     }
//     vector<wstring> blocks;
//     size_t filePos = 0;
//     while (filePos < fileText.size()) {
//         wstring block = fileText.substr(filePos, block_length);
//         blocks.push_back(block);
//         filePos += block_length;
//     }
//     debugFile << L"*** Encrypting " << to_wstring(FILENUM) << L"_in.dat, size " << fileText.size() << L" -> " << to_wstring(FILENUM) << L"_encrypted.txt * **\n" << endl;
//     int blockCount = 0;
//     int charCount = 0;
//     for (wstring block : blocks) {
//         debugFile << L"--- RSACodec::encryptStream block #" << dec << blockCount << L", max length " << dec << block_length << L" ---\n" << endl;
//         debugFile << L"BlockReader::readData - Requested count " << dec << block_length << L" bytes, got" << endl;
//         cpp_int plaintext_number = 0;
//         for (wchar_t c : block) {
//             if (int(char(c)) < 0) {
//                 //unicode
//                 debugFile << "[" << dec << charCount << "]" << " '0x" << hex << uppercase << int(c) << "' ";
//             }
//             else {
//                 // has ascii representation
//                 if (c == L'\n') {
//                     debugFile << "[" << dec << charCount << "]" << " '\\n' ";
//                 }
//                 else if (c == L'\r') {
//                     debugFile << "[" << dec << charCount << "]" << " '\\r' ";
//                 }
//                 else if (c == L'\t') {
//                     debugFile << "[" << dec << charCount << "]" << " '\\t' ";
//                 }
//                 else {
//                     debugFile << "[" << dec << charCount << "]" << " '" << c << "' ";
//                 }
//             }
//             plaintext_number = plaintext_number * 256 + static_cast<unsigned char>(c);
//             charCount++;
//         }
//         cpp_int ciphertext_number = rsa_encrypt(plaintext_number, E, N);
//         tempBuffer << hex << uppercase << ciphertext_number;
//         tempStr = tempBuffer.str();
//         tempBuffer.str("");
//         tempBuffer.clear();
//         wstring ciphertextWString = wstring(tempStr.begin(), tempStr.end());
//         tempBuffer << hex << uppercase << plaintext_number;
//         tempStr = tempBuffer.str();
//         tempBuffer.str("");
//         tempBuffer.clear();
//         wstring plaintextWString = wstring(tempStr.begin(), tempStr.end());
//         debugFile << endl;

//         if (charCount == block_length) {
//             encryptFile << hex << block_length << " ";
//             debugFile << L"BlockReader::readData - Read 0x" << plaintextWString << L"as " << dec << block_length << L" bytes" << endl;
//         }
//         else {
//             encryptFile << hex << charCount << " ";
//             debugFile << L"BlockReader::readData - Read 0x" << plaintextWString << L"as " << dec << charCount << L" bytes" << endl;
//         }
//         debugFile << L"\nRSAAlgorithm::encrypt 0x" << plaintextWString << " -> 0x" << ciphertextWString << L"\n" << endl;
//         encryptFile << ciphertextWString << endl;
//         charCount = 0;
//         blockCount++;
//     }
//     encryptFile.close();

//     wifstream encryptedFile(to_string(FILENUM) + "_encrypted.txt");
//     wofstream decryptedFile(to_string(FILENUM) + "_decrypted.dat");
//     //wss.str(L"");
//     //wss.clear();
//     //wss << encryptedFile.rdbuf();
//     //fileText = wss.str();
//     debugFile << L"Encrypted file " << to_wstring(FILENUM) << L"_encrypted.txt size is " << fileText.size() << "\n" << endl;
//     // vector<pair<block_length, ciphertext>>
//     vector<pair<int, wstring>> encrypted_blocks;
//     wstring line;
//     size_t pos = 0;
//     wstring block_length_wstr;
//     wstring ciphertext;
//     while (getline(encryptedFile, line)){
//         block_length_wstr = line.substr(0, line.find(' '));
//         ciphertext = line.substr(line.find(' ')+1, line.size());
//         pair<int, wstring> temp;
//         temp.first = stoi(block_length_wstr, nullptr, 16);
//         wstring plaintext_hex = decryptRSA(ciphertext, N, D, debugFile, temp.first);
//         temp.second = plaintext_hex;
//         encrypted_blocks.push_back(temp);
//     }

//     for (const auto& encrypted_block : encrypted_blocks) {
//         wstring text_hex = encrypted_block.second;
//         for (size_t i = 0; i < text_hex.size(); i+=2) {
//             wstring hex_character = text_hex.substr(i, 2);
//             int character_val;
//             wstringstream(hex_character) >> hex >> character_val;
//             if (int(char(character_val)) < 0) {
//                 wstring unicode_code = L"";
//                 unicode_code += hex_character;
//                 size_t pos = i + 2;
//                 wstringstream(text_hex.substr(pos, 2)) >> hex >> character_val;
//                 while (int(char(character_val)) < 0) {
//                     unicode_code += text_hex.substr(pos, 2);
//                     pos += 2;
//                     wstringstream(text_hex.substr(pos, 2)) >> hex >> character_val;
//                 }
//                 //unicode_code = unicode_code.substr(2, unicode_code.size());
//                 decryptedFile << unicode_code;
//                 i = pos - 2;
//             }
//             else {
//                 decryptedFile << wchar_t(character_val);
//             }
//             //wcout << static_cast<wchar_t>(character_val) << " ";
//         }
    
//     }
//     // Convert the hexadecimal code to an integer
//     // Output the Unicode character

//     // e2   80   a2   09   41   0d   0a
//     // uni  bullet p / t   A    \r   \n

//     //wstring code = L"2022"; // last two bytes of E2 80 A2
//     //unsigned long unicode_code = stoul(code, nullptr, 16);
//     //wchar_t character = static_cast<wchar_t>(unicode_code);
//     //wcout << character << endl;

//     debugFile << L"***Decrypting " << to_wstring(FILENUM) << L"_encrypted.txt, " << fileText.size() << L" -> " << to_wstring(FILENUM) << "_decrypted.dat * **\n" << endl;
//     // loop through each line in the encrypted file
//     // grab pairs of hex values and turn them into characters
//     // if int(char) is negative then add anothe char until the whole thing becomes positive
//     return 0;
// }


