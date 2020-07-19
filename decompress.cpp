#include "binaryTree.h"
#include "huffmanTree.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

void output_helper(Node *current, const string& line, const HuffmanTree& result_tree) {
    if (result_tree.findPath(current->getstr()) == line) {
        cout << current->getstr();
    } else {
        if (current->leftSubtree() != nullptr && current->rightSubtree() == nullptr) {
            output_helper(current->leftSubtree(), line, result_tree);
        } else if (current->leftSubtree() == nullptr && current->rightSubtree() != nullptr) {
            output_helper(current->rightSubtree(), line, result_tree);
        } else if (current->leftSubtree() != nullptr && current->rightSubtree() != nullptr) {
            output_helper(current->leftSubtree(), line, result_tree);
            output_helper(current->rightSubtree(), line, result_tree);
        }
    }
}

int main(int argc, char *argv[]) {
    ifstream ifile;
    HuffmanTree result_tree(argv[1]);
    ifile.open(argv[2]);
    string line;
    istringstream istream_output;
    while (getline(ifile, line, ' ')) {
        output_helper(result_tree.root,line,result_tree);
    }
    ifile.close();
    cout << endl;
}