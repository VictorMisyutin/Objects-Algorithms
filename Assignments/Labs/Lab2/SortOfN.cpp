#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include<windows.h>

using namespace std;

void sortFile(string num){
    ifstream inFile;
    string line;
    inFile.open("in_abc" + num + ".txt");

    int k = 0;
    if (inFile.is_open()) {
        string numberString = "";
        int charNumber = 0;
        // get k
        getline(inFile, line);
        size_t pos = line.find('=');
        for(char c : line.substr(pos + 2)){
            charNumber = int(c) - 96;
            numberString.append(to_string(charNumber));
        }
        try{
            k = stoi(numberString);
        }
        catch (const invalid_argument& e){
            k = 270000;
        }
        
        string *words = new string[k+1];

        while(getline(inFile, line)){
            stringstream ss(line);
            string word = "";

            while (ss >> word) {
                numberString = "";
                // convert word into lower case
                for (char &c : word) {
                    c = tolower(c);
                }

                // convert word into number
                for(char c : word){
                    charNumber = int(c) - 96;
                    numberString.append(charNumber < 10 ? "0" + to_string(charNumber): to_string(charNumber));
                }
                // add following zeros if needed
                if(numberString.length() < 6){
                    for(int i = 0; 6 != numberString.length(); i++){
                        numberString.append("0");
                    }
                }

                try{
                    words[stoi(numberString)] = word;
                }
                catch (const invalid_argument& e){
                    cout << "ERROR, Program Terminated" << endl;
                    exit(EXIT_SUCCESS);
                }
            }
        }

        ofstream outFile;
        outFile.open ("out_abc" + num + ".txt");
        for (int i = 0; i < k+1; i++) {
            if(words[i] != ""){
                outFile << words[i] << " ";
            }
        }
        // free large array before ending function 
        delete[] words;
    }
    else{
        cout << "File does not exist." << endl; 
    }
}

int main(){
    sortFile("10");
    sortFile("100");
}