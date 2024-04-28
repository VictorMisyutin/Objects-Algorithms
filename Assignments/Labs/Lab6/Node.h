#ifndef NODE_H
#define NODE_H

#include <string>
#include <iostream>

using namespace std;

class Node {
private:
    int asciiCode;
    string character;
    int frequency;
    // string bitSeries;
    Node* left;
    Node* right;
public:
    Node() : asciiCode(-1), character(""), frequency(0), left(nullptr), right(nullptr) {};
    Node(int a, string c, int f, Node* l = nullptr, Node* r = nullptr) : asciiCode(a), character(c), frequency(f), left(l), right(r) {};
    int GetAsciiCode();
    void SetAsciiCode(int a);
    string GetCharacter();
    void SetCharacterCode(string s);
    // string GetBitSeries();
    int GetFrequency();
    void SetFrequency(int f);
    Node* GetLeftChild();
    void SetLeftChild(Node* n);
    Node* GetRightChild();
    void SetRightChild(Node* n);
    void Print();
};
#endif