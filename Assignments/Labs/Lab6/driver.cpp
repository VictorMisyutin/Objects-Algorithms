#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>
#include "MinHeap.h"

using namespace std;

void RemoveLastCharacterFromFile(const string filename) {
    ifstream inputFile(filename);
    string content((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>());
    inputFile.close();
    if (!content.empty()) {
        content.pop_back();
        ofstream outputFile(filename);
        if (!outputFile)
            return;
        outputFile << content;
        outputFile.close();
    }
}

void BuildHuffmanTable(Node* root, vector<pair<string, string>>& ht, ofstream& file, string bitPath) {
    if (root->GetAsciiCode() != -1) {
        file << root->GetAsciiCode() << " '" << root->GetCharacter() << "' {" << bitPath << "}" << endl;
        ht.push_back(make_pair(root->GetCharacter(), bitPath));
    }
    if (root->GetLeftChild() == nullptr && root->GetRightChild() == nullptr) {
        // leaf node
        return;
    }
    else if (root->GetLeftChild() == nullptr) {
        // only has right child
        BuildHuffmanTable(root->GetRightChild(), ht, file, bitPath + "1");
    }
    else if (root->GetRightChild() == nullptr) {
        // only has left child
        BuildHuffmanTable(root->GetLeftChild(), ht, file, bitPath + "0");
    }
    else {
        // has both children
        BuildHuffmanTable(root->GetLeftChild(), ht, file, bitPath + "0");
        BuildHuffmanTable(root->GetRightChild(), ht, file, bitPath + "1");
    }
}

Node* BuildHuffmanTree(PriorityQueue& pq, vector<pair<string, string>>& ht, ofstream& file) {
    Node* rootNode = new Node(-1, "", 0, nullptr, nullptr);
    if (pq.Size() == 0) {
        return rootNode;
    }
    else if (pq.Size() == 1) {
        Node* temp = pq.pop();
        rootNode = new Node(temp->GetAsciiCode(), temp->GetCharacter(), temp->GetFrequency(), nullptr, nullptr);
        BuildHuffmanTable(rootNode, ht, file, "0");
        return rootNode;
    }
    while (pq.Size() > 1) {
        Node* leftNode = pq.pop();
        Node* rightNode = pq.pop();
        int freqSum = leftNode->GetFrequency() + rightNode->GetFrequency();
        Node* internalNode = new Node(-1, "", freqSum, leftNode, rightNode);
        pq.enqueue(internalNode);
        rootNode = internalNode;
    }

    BuildHuffmanTable(rootNode, ht, file, "");
    return rootNode;
}

string huffmanValue(string c, vector<pair<string, string>>& ht) {
    for (auto& pair : ht)
        if (pair.first == c)
            return pair.second;
    return "";
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
    for (int m = 1; m < 12; m++) {
        ofstream debugFile("./" + to_string(m) + "_debug.txt");
        ofstream tempOpen("./" + to_string(m) + "_in.txt", ios::app);
        tempOpen << " ";
        tempOpen.close();
        ifstream inFile("./" + to_string(m) + "_in.txt");
        cout << "*** Testing File " << to_string(m) << "_in.txt, debug output file " << to_string(m) << "_debug.txt ***" << endl;
        string line = "";
        string character = "";
        vector<pair<string, int>> characters_frequency;
        characters_frequency.push_back(make_pair("\\r", -1));
        characters_frequency.push_back(make_pair("\\n", -1));

        int fileLength = 0;
        while (getline(inFile, line)) {
            fileLength++;
            for (int i = 0; i < line.length(); i++) {
                character = line[i];
                auto it = find_if(characters_frequency.begin(), characters_frequency.end(), [&character](const pair<string, int>& p) {
                    return p.first == character;
                    });
                if (it != characters_frequency.end()) {
                    it->second++;
                }
                else {
                    characters_frequency.push_back(make_pair(character, 1));
                }
            }
            characters_frequency[0].second++;
            characters_frequency[1].second++;
        }
        inFile.clear();
        inFile.seekg(0);

        for (int j = 0; j < characters_frequency.size(); j++) {
            pair<string, int>& p = characters_frequency[j];
            if (p.first == " ") p.second--;
            if (p.second == 0)
            {
                characters_frequency.erase(characters_frequency.begin() + j);
                j--;
            }
        }

        string output_character = "";
        int asciiCode = 0;
        PriorityQueue pq;
        vector<pair<string, string>> huffmanValues;
        debugFile << "countCharacters:\n" << endl;
        for (const auto& pair : characters_frequency) {
            if (pair.first == "\\n") {
                output_character = "\\n";
                asciiCode = 10;
            }
            else if (pair.first == "\\r") {
                output_character = "\\r";
                asciiCode = 13;
            }
            else {
                output_character = pair.first;
                asciiCode = int(pair.first[0]);
            }
            debugFile << to_string(asciiCode) << " '" << output_character << "' {" << to_string(pair.second) << "}" << endl;
            Node* node = new Node(asciiCode, output_character, pair.second);
            pq.enqueue(node);
        }

        debugFile << "\nprintQueue:\n" << endl;
        pq.Print(debugFile);

        debugFile << "\nmakeBitData:\n" << endl;
        Node* rootNode = BuildHuffmanTree(pq, huffmanValues, debugFile);
        debugFile.close();

        ofstream encodedOut("./" + to_string(m) + "_encoded.txt");
        string encodedString = "";
        int fileLengthTwo = 0;
        while (getline(inFile, line)) {
            fileLengthTwo++;
            if (fileLengthTwo == fileLength)
                line.pop_back();
            for (int i = 0; i < line.length(); i++) {
                character = line[i];
                encodedString += huffmanValue(character, huffmanValues);
            }
            if (fileLengthTwo != fileLength) {
                encodedString += huffmanValue("\\r", huffmanValues);
                encodedString += huffmanValue("\\n", huffmanValues);
            }
        }
        inFile.close();
        encodedOut << encodedString;
        RemoveLastCharacterFromFile("./" + to_string(m) + "_in.txt");
        encodedOut.close();

        ifstream encodedFile("./" + to_string(m) + "_encoded.txt");
        ofstream decodedFile("./" + to_string(m) + "_decoded.txt");
        getline(encodedFile, line);
        encodedFile.close();

        // handle case where tere is just one repeated character:
        if (rootNode->GetAsciiCode() != -1 && rootNode->GetLeftChild() == nullptr && rootNode->GetRightChild() == nullptr) {
            for (char c : line) {
                decodedFile << rootNode->GetCharacter();
            }
            decodedFile.close();
            if (compareFiles("./" + to_string(m) + "_in.txt", "./" + to_string(m) + "_decoded.txt")) {
                cout << "OK" << endl;
            }
            else {
                cout << "fail:" << to_string(m) << endl;
            }
            debugFile.close();
        }
        else {
            Node currentNode = *rootNode;
            for (char c : line) {
                if (c == '0') {
                    currentNode = *currentNode.GetLeftChild();
                }
                else {
                    currentNode = *currentNode.GetRightChild();
                }
                if (currentNode.GetAsciiCode() != -1) {
                    if (currentNode.GetCharacter() == "\\n") {
                        decodedFile << "\n";
                    }
                    else if (currentNode.GetCharacter() == "\\r") {
                        // '\n' already does '\r' automatically so I think I can just ignore these for now.
                        // do nothing
                    }
                    else
                        decodedFile << currentNode.GetCharacter();
                    currentNode = *rootNode;
                }
            }
            decodedFile.close();

            if (compareFiles("./" + to_string(m) + "_in.txt", "./" + to_string(m) + "_decoded.txt")) {
                cout << "OK" << endl;
            }
            else {
                cout << "fail:" << to_string(m) << endl;
            }
        }
    }
    return 0;
}
