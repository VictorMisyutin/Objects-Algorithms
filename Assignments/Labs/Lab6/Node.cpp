#include "Node.h"

int Node::GetAsciiCode() {
    return asciiCode;
}
void Node::SetAsciiCode(int a) {
    asciiCode = a;
}

string Node::GetCharacter() {
    return character;
}
void Node::SetCharacterCode(string c) {
    character = c;
}
int Node::GetFrequency() {
    return frequency;
}
void Node::SetFrequency(int f) {
    frequency = f;
}

Node* Node::GetLeftChild() {
    return left;
}
void Node::SetLeftChild(Node* n) {
    left = n;
}
Node* Node::GetRightChild() {
    return right;
}
void Node::SetRightChild(Node* n) {
    right = n;
}
void Node::Print() {
    cout << asciiCode << " '" << character << "' {" << frequency << "}" << endl;
}
