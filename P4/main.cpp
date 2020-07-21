#include <iostream>
#include <string>
#include "binaryTree.h"
using namespace std;

int main() {
    Node* n1 = new Node("a",1);
    Node* n2 = new Node("b",2);
    Node* n3 = new Node("c",3);
    Node* n4 = new Node("d",4);
    Node* n5 = new Node("e",5);
    Node* n6 = new Node("f",6);
    Node* n7 = new Node("g",7);
    n1->setleft(n2);
    n1->setright(n3);
    n2->setright(n4);
    n4->setleft(n6);
    n4->setright(n7);
    n3->setright(n5);
    BinaryTree b1(n1);
    BinaryTree b2;
    Node* n8 = new Node("dawdwa",1);
    Node* n9 = new Node("dadw",3);
    Node* n10 = new Node("dddd",5);
    Node* n11 = new Node("fff",9);
    n8->setright(n9);
    n9->setright(n10);
    n10->setleft(n11);
    BinaryTree b3(n8);
    Node* n12 = new Node("dawdwa",1);
    Node* n13 = new Node("dadw",3);
    Node* n14 = new Node("dddd",5);
    n12->setright(n13);
    n13->setright(n14);
    BinaryTree b4(n12);
    Node* n15 = new Node("dawdwa",4);
    Node* n16 = new Node("dadw",6);
    Node* n17 = new Node("dddd",7);
    n15->setleft(n16);
    n15->setright(n17);
    BinaryTree b5(n15);
    Node* n18 = new Node("dawdwa",4);
    Node* n19 = new Node("dadw",6);
    Node* n20 = new Node("dddd",8);
    n18->setleft(n19);
    n18->setright(n20);
    BinaryTree b6(n18);
    cout<<b1.findPath("a")<<endl;
    cout<<b1.findPath("da")<<endl;
    cout<<b1.findPath("d")<<endl;
    cout<<b1.findPath("e")<<endl;
    cout<<b1.findPath("f")<<endl;
    cout<<b1.sum()<<endl;
    cout<<b2.sum()<<endl;
    cout<<b1.depth()<<endl;
    cout<<b2.depth()<<endl;
    b1.preorder_num();
    cout<<endl;
    b1.inorder_str();
    cout<<endl;
    b1.postorder_num();
    cout<<endl;
    b2.preorder_num();
    b2.inorder_str();
    b2.postorder_num();
    cout<<endl;
    cout<<b1.allPathSumGreater(9)<<endl;
    cout<<b1.allPathSumGreater(8)<<endl;
    cout<<b1.allPathSumGreater(2)<<endl;
    cout<<b2.covered_by(b1)<<endl;
    cout<<b3.covered_by(b1)<<endl;
    cout<<b4.covered_by(b1)<<endl;
    cout<<b5.covered_by(b1)<<endl;
    cout<<b6.covered_by(b1)<<endl;
    cout<<b2.contained_by(b1)<<endl;
    cout<<b3.contained_by(b1)<<endl;
    cout<<b4.contained_by(b1)<<endl;
    cout<<b5.contained_by(b1)<<endl;//diff 0->1(hygg)
    cout<<b6.contained_by(b1)<<endl;
    cout<<b2.contained_by(b2)<<endl;
    cout<<b2.covered_by(b2)<<endl;
    cout<<b2.contained_by(b1.copy())<<endl;
    cout<<b3.contained_by(b1.copy())<<endl;
    cout<<b4.contained_by(b1.copy())<<endl;
    cout<<b5.contained_by(b1.copy())<<endl;//diff 0->1(hygg)
    cout<<b6.contained_by(b1.copy())<<endl;
    return 0;
}
