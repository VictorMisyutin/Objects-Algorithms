#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main() {
    bool end = false;
    ifstream inFile;
    string line;
    int target;
    int count = 1;
    while(!end && count < 10){
        inFile.open("in" + to_string(count) + ".txt");

        if (inFile.is_open()) {
            getline(inFile, line); // skip first line

            // get target num
            getline(inFile, line);
            target = stoi(line);

            // convert numbers to array
            getline(inFile, line);

            vector<int> numbers;
            int startPos = 0;

            // convert line to vector
            for (int i = 0; i < line.length(); ++i) {
                if (line[i] == ' ' || i == line.length() - 1) {
                    string numStr = line.substr(startPos, i - startPos + 1);
                    int num = stoi(numStr);
                    numbers.push_back(num);
                    startPos = i + 1;
                }
            }

            // do algorithm

            O(n^2) solution
            int num1;
            int num2;
            bool found = false;

            for (int i = 0; i < numbers.size() - 1 && !found; ++i) {
                for (int j = i; j < numbers.size() && !found; ++j) {
                    if (numbers[i] + numbers[j] == target) {
                        num1 = numbers[i];
                        num2 = numbers[j];
                        found = true;
                    }
                }
            }


            // output to file
            ofstream outFile;
            outFile.open ("out" + to_string(count) + ".txt");
            outFile << target << "\nSumOfK\n";
            for (int i = 0; i < numbers.size(); ++i) {
                outFile << numbers[i] << " ";
            }
            outFile << "\nExercise1 calculation complexity O(n^2)\n";
            if (found){
                outFile << "Yes\n" << num1 << " + " << num2 << " = " << to_string(target) << endl;
            }
            else{
                outFile << "No" << endl;
            }
            outFile.close();
            inFile.close();
        } else {
            end = true;
        }
        count ++;
    }

    return 0;
}
