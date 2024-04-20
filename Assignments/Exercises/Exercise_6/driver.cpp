#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

#include "MinHeap.cpp"

using namespace std;

void BuildHuffmanTable(Node* root, unordered_map<string, string>& ht, ofstream& file, string bitPath) {
    if(root->GetAsciiCode() != -1){
        file << root->GetAsciiCode() << " '" << root->GetCharacter() << "' {" << bitPath << "}" << endl;
        ht[root->GetCharacter()] = bitPath;
    }
    if(root->GetLeftChild() == nullptr && root->GetRightChild() == nullptr){
        // leaf node
        return;
    }
    else if(root->GetLeftChild() == nullptr){
        // only has right child
        BuildHuffmanTable(root->GetRightChild(), ht, file, bitPath + "1");
    }
    else if(root->GetRightChild() == nullptr){
        // only has left child
        BuildHuffmanTable(root->GetLeftChild(), ht, file, bitPath + "0");
    }
    else{
        // has both children
        BuildHuffmanTable(root->GetLeftChild(), ht, file, bitPath + "0");
        BuildHuffmanTable(root->GetRightChild(), ht, file, bitPath + "1");
    }
}

void HuffmanTree(PriorityQueue& pq, unordered_map<string, string>& ht, ofstream& file) {
    // Node* lastLeft;
    // Node* lastRight;
    Node* lastNode;
    int pass = 0;
    while (pq.Size() > 1) {
        Node* leftNode = pq.pop();
        Node* rightNode = pq.pop();
        // int freqSum = leftChar.GetFrequency() + rightChar.GetFrequency();
        int freqSum = leftNode->GetFrequency() + rightNode->GetFrequency();
        Node* internalNode = new Node(-1, "", freqSum, leftNode, rightNode);
        pq.enqueue(internalNode);
        lastNode = internalNode;
    }
    // return new Node(pq.peek().GetAsciiCode(), pq.peek().GetCharacter(), pq.peek().GetFrequency(), pq.peek(), lastRight);
    BuildHuffmanTable(lastNode, ht, file, "");
}

int main(){
    for(int i = 5 ; i < 15 ;i+=9 ){
        ifstream inFile(to_string(i) + "_in.txt");
        ofstream debugFile( to_string(i) + "_debug.txt");

        string line = "";
        string character = "";
        unordered_map<string, int> characters_map = {};

        characters_map["\\r"] = 0;
        characters_map["\\n"] = 0;

        while(getline(inFile, line)){
            cout << "new line" << endl;
            for(int i = 0; i < line.length(); i++){
                character = line[i];
                if(characters_map.find(character) == characters_map.end())
                    characters_map[character] =  1;
                else{
                    characters_map[character] += 1;
                }
            }
            characters_map["\\r"] += 1;
            characters_map["\\n"] += 1;
        }
        cout << endl;
        // back to beginning
        inFile.clear();
        inFile.seekg(0);
        
        string output_character = "";
        int asciiCode = 0;
        PriorityQueue pq;
        unordered_map<string, string> hoffmanValues = {};
        debugFile << "countCharacters:\n" << endl;
        for(auto pair: characters_map){
            if(pair.first == "\\n") {
                output_character = "\\n";
                asciiCode = 10;        
            }
            else if(pair.first == "\\r") {
                output_character = "\\r";
                asciiCode = 13;
            }
            else{
                output_character = pair.first;
                asciiCode = int(pair.first[0]); 
            }
            debugFile << to_string(asciiCode) << " '" << output_character << "' {" << to_string(pair.second) << "}" << endl;
            Node* node = new Node(asciiCode, output_character,pair.second);
            pq.enqueue(node);
        }

        debugFile << "\nprintQueue:\n" << endl;
        pq.Print(debugFile);


        debugFile << "\nmakeBitData:\n" << endl;
        HuffmanTree(pq, hoffmanValues, debugFile);

        ofstream encodedOut(to_string(i) + "_encoded.txt");
        string encodedString = "";
        string search = "";
        while(getline(inFile, line)){
            for(int i = 0; i < line.length(); i++){
                character = line[i];
                encodedString = encodedString + hoffmanValues[character];
            }
            encodedString = encodedString + hoffmanValues["\\r"];
            encodedString = encodedString + hoffmanValues["\\n"];
        }
        encodedOut << encodedString;
    }
    return 0;
}
