#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void sortFile(string num){
    ifstream inFile;
    string line;
    inFile.open("in" + num + ".txt");

    if (inFile.is_open()) {
        getline(inFile, line);
        int k = stoi(line);

        vector<int> numbers;
        while(getline(inFile, line)){

            size_t startIndex = 0;

            while (startIndex < line.size()) {
                size_t endIndex = line.find(' ', startIndex);

                string numberStr = line.substr(startIndex, endIndex - startIndex);
                int number;
                try{
                    number = stoi(numberStr);
                }
                catch (const std::invalid_argument& e){
                    number = 0;
                }

                numbers.push_back(number);

                startIndex = endIndex + 1;
            }
        }
        int n = numbers.size();

        // begin sorting
        int A[k] = {0};
        for (int i: numbers) {
            A[i] = A[i] + 1;
        }

        // display/output
        ofstream outFile;
        outFile.open ("out" + num + ".txt");
        for (int i = 0; i < k; i++) {
            if(A[i] > 0){
                for(int j = A[i] ; j > 0;j--){
                    outFile << i << " ";
                }
            }
        }

    }
    else{
        cout << "File does not exist." << endl; 
    }
}

int main(){
    sortFile("10");
    sortFile("100");

}