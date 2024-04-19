#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

#include "priorityQueue.cpp"

using namespace std;

int main(){
    ifstream inFile("5_in.txt");
    ofstream debugFile("5_debug.txt");

    string line = "";
    string character = "";
    unordered_map<string, int> characters_map = {};

    characters_map["\\n"] = 0;
    characters_map["\\r"] = 0;

    while(getline(inFile, line)){
        for(int i = 0; i < line.length(); i++){
            character = line[i];
            if(characters_map.find(character) == characters_map.end())
                characters_map[character] =  1;
            else{
                characters_map[character] += 1;
            }
        }
        characters_map["\\n"] += 1;
        characters_map["\\r"] += 1;
    }

    string output_character = "";
    int asciiCode = 0;
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
    }


    return 0;
}