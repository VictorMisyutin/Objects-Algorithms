#include "Edge.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool compareEdges(const Edge& e1, const Edge& e2) {
    return e1.weight < e2.weight;
}

Node* findRoot(Node* node) {
    while (node->GetParent() != nullptr) {
        node = node->GetParent();
    }
    return node;
}

void mergeSets(Node* root1, Node* root2) {
    if (root1->GetRank() < root2->GetRank()) {
        root1->SetParent(root2);
    }
    else if (root1->GetRank() > root2->GetRank()) {
        root2->SetParent(root1);
    }
    else {
        root1->SetParent(root2);
        root2->SetRank(root2->GetRank() + 1);
    }
}

int main() {
    for (int i = 2; i < 4; i++) {
        ifstream inFile("in" + to_string(i) + "_edges" + ".txt");
        ofstream outFile("out" + to_string(i) + "_edges" + ".txt");

        vector<Node*> nodes;
        vector<Edge> edges;

        string temp1, temp2, temp3;
        getline(inFile, temp1); // Skip first line 

        while (inFile >> temp1 >> temp2 >> temp3) {
            int val1 = stoi(temp1);
            int val2 = stoi(temp2);
            int weight = stoi(temp3);

            Node* node1 = nullptr;
            auto it1 = find_if(nodes.begin(), nodes.end(), [&](Node* n) { return n->GetValue() == val1; });
            if (it1 == nodes.end()) {
                node1 = new Node(val1);
                nodes.push_back(node1);
            }
            else {
                node1 = *it1;
            }

            Node* node2 = nullptr;
            auto it2 = find_if(nodes.begin(), nodes.end(), [&](Node* n) { return n->GetValue() == val2; });
            if (it2 == nodes.end()) {
                node2 = new Node(val2);
                nodes.push_back(node2);
            }
            else {
                node2 = *it2;
            }

            // Create edge and add it to the list of edges
            edges.emplace_back(node1, node2, weight);
        }

        sort(edges.begin(), edges.end(), compareEdges); // sort edges by weight

        for (Node* node : nodes) {
            node->SetParent(nullptr);
            node->SetRank(0);
        }

        outFile << "Graph edges: vertice1, vertice2, weight of the edge\n" << endl;

        vector<Edge> mstEdges;
        for (const Edge& edge : edges) { // loop through tree for algo
            Node* root1 = findRoot(edge.node1);
            Node* root2 = findRoot(edge.node2);

            if (root1 != root2) {
                mstEdges.push_back(edge);
                mergeSets(root1, root2);
            }

            outFile << "edge: " << edge.node1->GetValue() << ", " << edge.node2->GetValue() << ", " << edge.weight << endl;
        }
        outFile << "\nKruskal spanning tree edges: vertice1, vertice2, weight of the edge\n" << endl;

        int totalWeight = 0;
        for (const Edge& edge : mstEdges) {
            outFile << "edge: " << edge.node1->GetValue() << ", " << edge.node2->GetValue() << ", " << edge.weight << endl;
            totalWeight += edge.weight;
        }
        outFile << "Kruskal spanning tree weight is " << to_string(totalWeight) << endl;


        inFile.close();
        outFile.close();
    }

    return 0;
}
