#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>
#include <fstream> // File stream for file operations
#include <functional> // Include for std::function

struct Node {
    char data;
    int frequency;
    Node* left;
    Node* right;

    Node(char data, int frequency) : data(data), frequency(frequency), left(nullptr), right(nullptr) {}
};

// Compare functor for priority queue
struct Compare {
    bool operator()(const Node* lhs, const Node* rhs) const {
        return lhs->frequency > rhs->frequency;
    }
};

// Function for Huffman tree traversal to generate codes
void traverse(Node* node, const std::string& code, std::unordered_map<char, std::string>& encoding) {
    if (node) {
        if (!node->left && !node->right) {
            encoding[node->data] = code;
        } else {
            traverse(node->left, code + '0', encoding);
            traverse(node->right, code + '1', encoding);
        }
    }
}

std::unordered_map<char, std::string> huffmanEncoding(const std::string& input_string) {
    std::unordered_map<char, int> frequencies;
    // Count character frequencies
    for (char c : input_string) {
        frequencies[c]++;
    }

    // Priority queue to build Huffman tree
    std::priority_queue<Node*, std::vector<Node*>, Compare> pq;
    for (const auto& pair : frequencies) {
        pq.push(new Node(pair.first, pair.second));
    }

    // Build Huffman tree
    while (pq.size() > 1) {
        Node* left = pq.top();
        pq.pop();
        Node* right = pq.top();
        pq.pop();
        Node* parent = new Node('\0', left->frequency + right->frequency);
        parent->left = left;
        parent->right = right;
        pq.push(parent);
    }

    // Generate Huffman codes
    std::unordered_map<char, std::string> encoding;
    if (!pq.empty()) {
        Node* root = pq.top();
        // Traverse the tree to generate codes
        traverse(root, "", encoding);
        delete root;
    }

    return encoding;
}

int main() {
    std::ifstream file("../Exercise_6/5_in.txt"); // Open the input file
    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    std::string input_string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>()); // Read file content into a string
    file.close(); // Close the file

    std::unordered_map<char, std::string> huffman_encoding = huffmanEncoding(input_string);
    for (const auto& pair : huffman_encoding) {
        std::cout << "Character: " << pair.first << ", Huffman Code: " << pair.second << std::endl;
    }
    return 0;
}