#include "binaryTree.h"
#include "huffmanTree.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;


int main(int argc, char *argv[]) {
    int frequency[28];
    int i, num_character = 0;
    for (i = 0; i < 28; i++) {
        frequency[i] = 0;
    }
    ifstream ifile;
    if (argc == 3) {
        ifile.open(argv[2]);
    } else {
        ifile.open(argv[1]);
    }
    string line;
    istringstream istream;
    char medium;
    while (getline(ifile, line)) {
        frequency[27]++;
        istream.str(line);
        istream >> medium;
        for (i = 0; i < line.length(); i++) {
            //cout<<medium<<endl;
            if (medium == ' ') {
                frequency[26]++;
            } else {
                frequency[medium - 97]++;
            }
            istream >> medium;
        }
        //cout<<"!!"<<endl;
    }
    ifile.close();
    for (i = 0; i < 28; i++) {
        // cout << i << " " << frequency[i] << endl;
        if (frequency[i] != 0) {
            num_character++;
        }
    }
    Node *characters[num_character];
    int n = 0;
    for (i = 0; i < 27; i++) {
        if (frequency[i] != 0) {
            if (i == 26) {
                characters[n] = new Node(" ", frequency[i]);
            } else {
                char a = i + 97;
                string b(1, a);
                characters[n] = new Node(b, frequency[i]);
            }
            n++;
        }
    }
    characters[n] = new Node("\n", frequency[27]);
    Node *original_characters[num_character * 2];
    for (i = 0; i < num_character; i++) {
        original_characters[i] = characters[i];
    }
    int total_num_nodes = num_character;
    int smallest_frequency;
    int smallest_index[2];
    while (num_character > 1) {
        smallest_index[0] = 0;
        smallest_index[1] = 0;
        smallest_frequency = characters[0]->getnum();
        for (i = 0; i < num_character; i++) {
            if (smallest_frequency > characters[i]->getnum()) {
                smallest_frequency = characters[i]->getnum();
                smallest_index[0] = i;
            } else if (smallest_frequency == characters[i]->getnum()) {
                if (characters[smallest_index[0]]->getstr() > characters[i]->getstr()) {
                    smallest_frequency = characters[i]->getnum();
                    smallest_index[0] = i;
                }
            }
        }
        if (smallest_index[0] != 0) {
            smallest_frequency = characters[0]->getnum();
        } else {
            smallest_frequency = characters[1]->getnum();
        }
        for (i = 0; i < num_character; i++) {
            if (i != smallest_index[0]) {
                if (smallest_frequency > characters[i]->getnum()) {
                    smallest_frequency = characters[i]->getnum();
                    smallest_index[1] = i;
                } else if (smallest_frequency == characters[i]->getnum()) {
                    if (characters[smallest_index[1]]->getstr() >= characters[i]->getstr()) {
                        smallest_frequency = characters[i]->getnum();
                        smallest_index[1] = i;
                    }
                }
            }
        }
        //cout << "!!!! "<<smallest_index[0] << " " << smallest_index[1]<<"!" << endl;
        Node *new_node = Node::mergeNodes(characters[smallest_index[1]],
                                          characters[smallest_index[0]]);
        characters[smallest_index[0]] = new_node;
        original_characters[total_num_nodes] = new_node;
        total_num_nodes++;
        for (i = smallest_index[1]; i < num_character - 1; i++) {
            characters[i] = characters[i + 1];
        }
        num_character--;
        /*
        cout<<"characters: "<<endl;
        for (i = 0; i < num_character; i++) {
            cout << i << " " << characters[i]->getstr() << " " << characters[i]->getnum() << endl;
        }
        cout<<"original characters: "<<endl;
        for (i = 0; i < total_num_nodes; i++) {
            cout << i << " " << original_characters[i]->getstr() << " " << original_characters[i]->getnum() << endl;
        }
        */
    }
    HuffmanTree result_tree(characters[0]);
    if (argc == 3) {
        result_tree.printTree();
    } else {
        ifile.open(argv[1]);
        string line_output;
        istringstream istream_output;
        char medium_output;
        while (getline(ifile, line_output)) {
            istream_output.str(line_output);
            istream_output >> medium_output;
            for (i = 0; i < line_output.length(); i++) {
                string output_string(1, medium_output);
                cout << result_tree.findPath(output_string)<<" ";
                istream_output >> medium_output;
            }
            cout << result_tree.findPath("\n")<<" ";
        }
        ifile.close();
        cout << endl;
    }

    // TODO: implement this function
}
