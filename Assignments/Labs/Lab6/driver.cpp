#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "MinHeap.cpp" // Assuming MinHeap.cpp contains the necessary definitions for your MinHeap

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
    } else if (root->GetLeftChild() == nullptr) {
        // only has right child
        BuildHuffmanTable(root->GetRightChild(), ht, file, bitPath + "1");
    } else if (root->GetRightChild() == nullptr) {
        // only has left child
        BuildHuffmanTable(root->GetLeftChild(), ht, file, bitPath + "0");
    } else {
        // has both children
        BuildHuffmanTable(root->GetLeftChild(), ht, file, bitPath + "0");
        BuildHuffmanTable(root->GetRightChild(), ht, file, bitPath + "1");
    }
}

void BuildHuffmanTree(PriorityQueue& pq, vector<pair<string, string>>& ht, ofstream& file) {
    Node* rootNode = nullptr;
    if(pq.Size() == 0){
        return;
    }
    else if(pq.Size() == 1){
        Node* temp = pq.pop();
        rootNode = new Node(temp->GetAsciiCode(), temp->GetCharacter(), temp->GetFrequency(), nullptr, nullptr);
        BuildHuffmanTable(rootNode, ht, file, "0");
        return;
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
}

string huffmanValue(string c, vector<pair<string, string>>& ht) {
    for (auto& pair : ht)
        if (pair.first == c)
            return pair.second;
    return "";
}

int main() {
    for (int m = 1; m < 12; m++) {
        ofstream debugFile("./outputs/" + to_string(m) + "_debug.txt");
        ofstream tempOpen("./inputs/" + to_string(m) + "_in.txt", ios::app);
        tempOpen << " ";
        tempOpen.close();
        ifstream inFile("./inputs/" + to_string(m) + "_in.txt");

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
                } else {
                    characters_frequency.push_back(make_pair(character, 1));
                }
            }
            characters_frequency[0].second++;
            characters_frequency[1].second++;
        }
        inFile.clear();
        inFile.seekg(0);

        for(int j = 0; j < characters_frequency.size(); j++){
            pair<string, int>& p = characters_frequency[j];
            if(p.first == " ") p.second--;
            if(p.second == 0)
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
            } else if (pair.first == "\\r") {
                output_character = "\\r";
                asciiCode = 13;
            } else {
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
        BuildHuffmanTree(pq, huffmanValues, debugFile);

        ofstream encodedOut("./outputs/" + to_string(m) + "_encoded.txt");
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
        encodedOut << encodedString;
        RemoveLastCharacterFromFile("./inputs/" + to_string(m) + "_in.txt");
    }
    return 0;
}
