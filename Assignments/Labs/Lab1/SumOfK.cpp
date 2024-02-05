#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void heapify(vector<int>& numbers, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && numbers[left] > numbers[largest]) {
        largest = left;
    }

    if (right < n && numbers[right] > numbers[largest]) {
        largest = right;
    }

    if (largest != i) {
        swap(numbers[i], numbers[largest]);
        heapify(numbers, n, largest);
    }
}

void heapSort(vector<int>& numbers) {
    int n = numbers.size();

    for (int i = n / 2 - 1; i >= 0; --i) {
        heapify(numbers, n, i);
    }

    for (int i = n - 1; i > 0; --i) {
        swap(numbers[0], numbers[i]);
        heapify(numbers, i, 0);
    }
}

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
                    try {
                        int num = stoi(numStr);
                        numbers.push_back(num);
                    } catch (const invalid_argument& e) {
                        cout << "Invalid number: " << numStr << endl;
                    }
                    startPos = i + 1;
                }
            }

            // sort vector
            vector<int> sortedNumbers = numbers;
            heapSort(sortedNumbers);
            // O(n) solution
            int num1;
            int num2;
            bool found = false;
            int leftp = 0;
            int rightp = sortedNumbers.size() - 1;

            while (leftp < rightp && !found) {
                int sum = sortedNumbers[leftp] + sortedNumbers[rightp];

                if (sum == target) {
                    num1 = sortedNumbers[leftp];
                    num2 = sortedNumbers[rightp];
                    found = true;
                } 
                else if (sum < target) {
                    leftp++;
                } 
                else {
                    rightp--;
                }
            }       

            // output to file
            ofstream outFile;
            outFile.open ("out" + to_string(count) + ".txt");
            outFile << target;
            outFile << "\nBefore Sorting\nSumOfK\n";
            for (int i = 0; i < numbers.size(); ++i) {
                outFile << numbers[i] << " ";
            }
            outFile << "\nAfter Sorting\nSumOfK\n";
            for (int i = 0; i < sortedNumbers.size(); ++i) {
                outFile << sortedNumbers[i] << " ";
            }
            outFile << "\nCalculation O(N) in Lab1 after sorting\n";
            if (found){
                outFile << "Yes\n" << num1 << "+" << num2 << "=" << to_string(target) << endl;
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
