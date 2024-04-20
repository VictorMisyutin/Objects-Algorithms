#include <iostream>
#include <fstream>
#include <string>
#include "MinHeap.cpp"
using namespace std;

void RemoveLastCharacterFromFile(const string filename) {
    ifstream inputFile(filename);
    string content((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>());
    inputFile.close();
    content.pop_back();
    ofstream outputFile(filename);
    if (!outputFile)
        return;
    outputFile << content;
    outputFile.close();
}

void BuildHuffmanTable(Node* root, vector<pair<string, string>>& ht, ofstream& file, string bitPath) {
    if(root->GetAsciiCode() != -1){
        file << root->GetAsciiCode() << " '" << root->GetCharacter() << "' {" << bitPath << "}" << endl;
        ht.push_back(pair(root->GetCharacter(), bitPath));
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

void HuffmanTree(PriorityQueue& pq, vector<pair<string, string>>& ht, ofstream& file) {
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
string hoffmanValue(string c, vector<pair<string, string>>& ht){
    for(auto pair:ht)
        if(pair.first == c) return pair.second;
    return ""; 

}
int main(){
    for(int m = 1 ; m < 12 ;m++ ){
        ofstream debugFile( to_string(m) + "_debug.txt");
        // write one space to end of file so that I can last line
        ofstream tempOpen( to_string(m) + "_in.txt", ios::app);
        tempOpen << " ";
        tempOpen.close();
        ifstream inFile(to_string(m) + "_in.txt");

        string line = "";
        string character = "";
        vector<pair<string, int>> characters_frequency = {};
        characters_frequency.push_back(pair("\\r", -1));
        characters_frequency.push_back(pair("\\n", -1));

        int fileLength = 0;
        while(getline(inFile, line)){
            fileLength++;
            for(int i = 0; i < line.length(); i++){
                character = line[i];
                bool found = false;
                for(int j = 0; j < characters_frequency.size(); j++){
                    if(characters_frequency[j].first == character){
                        characters_frequency[j].second++;
                        found = true;
                    }
                }
                if(!found){
                    characters_frequency.push_back(pair(character, 1));
                }
            }
            characters_frequency[0].second++;
            characters_frequency[1].second++;
        }
        // remove that temporary space
        for(int j = 0; j < characters_frequency.size(); j++){
            pair<string, int>& p = characters_frequency[j];
            if(p.first == " "){
                if(p.second == 1){
                    // erase the record
                    characters_frequency.erase(characters_frequency.begin() + j);
                }
                else{
                    p.second--;
                }
                break;
            }
        }



        // back to beginning
        inFile.clear();
        inFile.seekg(0);
        
        string output_character = "";
        int asciiCode = 0;
        PriorityQueue pq;
        // unordered_map<string, string> hoffmanValues = {};
        vector<pair<string, string>> hoffmanValues = {};
        debugFile << "countCharacters:\n" << endl;
        for(pair<string, int> pair: characters_frequency){
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
            cout << to_string(asciiCode) << " '" << output_character << "' {" << to_string(pair.second) << "}" << endl;
            debugFile << to_string(asciiCode) << " '" << output_character << "' {" << to_string(pair.second) << "}" << endl;
            Node* node = new Node(asciiCode, output_character,pair.second);
            pq.enqueue(node);
        }

        debugFile << "\nprintQueue:\n" << endl;
        pq.Print(debugFile);


        debugFile << "\nmakeBitData:\n" << endl;
        HuffmanTree(pq, hoffmanValues, debugFile);

        ofstream encodedOut(to_string(m) + "_encoded.txt");
        string encodedString = "";
        string search = "";
        int fileLengthTwo = 0;
        while(getline(inFile, line)){
            fileLengthTwo++;
            if(fileLengthTwo == fileLength) line.pop_back();
            for(int i = 0; i < line.length(); i++){
                character = line[i];
                encodedString = encodedString + hoffmanValue(character, hoffmanValues);
            }
            if(fileLengthTwo != fileLength){
                encodedString = encodedString + hoffmanValue("\\r", hoffmanValues);
                encodedString = encodedString + hoffmanValue("\\n", hoffmanValues);
            }
        }
        encodedOut << encodedString;
        RemoveLastCharacterFromFile(to_string(m) + "_in.txt");
    }
    return 0;
}
