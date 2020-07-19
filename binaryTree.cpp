#include "binaryTree.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

/* ================================== Node =================================== */
//TODO:delete cout
//TODO:add endl

Node::Node(const std::string &str, int num, Node *left, Node *right) : str(str), num(num), left(left), right(right) {

}

void deletion_helper(Node *current) {
    if (current->leftSubtree() != nullptr) {
        deletion_helper(current->leftSubtree());
    }
    if (current->rightSubtree() != nullptr) {
        deletion_helper(current->rightSubtree());
    }
    //cout<<current->getstr()<<endl;
    delete current;
}

Node *Node::leftSubtree() const {
    return left;

}

void Node::setleft(Node *n) {
    if (left == nullptr) {
        left = n;
    } else {
        deletion_helper(left);
        left=n;
    }
}

Node *Node::rightSubtree() const {
    return right;
}

void Node::setright(Node *n) {
    if (right == nullptr) {
        right = n;
    } else {
        deletion_helper(right);
        right=n;
    }
}

string Node::getstr() const {
    return str;
}

int Node::getnum() const {
    return num;
}

void Node::incnum() {
    num++;
}

Node *Node::mergeNodes(Node *leftNode, Node *rightNode) {
    int new_node_num = leftNode->num + rightNode->num;
    string left = leftNode->str, right = rightNode->str;
    left = left + right;
    Node *new_node = new Node(left, new_node_num, leftNode, rightNode);
    return new_node;
}

/* =============================== Binary Tree =============================== */

BinaryTree::BinaryTree(Node *rootNode) : root(rootNode) {

}


BinaryTree::~BinaryTree() {
   // cout<<"delete: "<<root<<endl;
    if(root!= nullptr){
        deletion_helper(root);
    }
}


string findpath_helper(const string &s, Node *current) {
    if (current->leftSubtree() != nullptr && current->rightSubtree() == nullptr) {
        if (current->leftSubtree()->getstr() == s) {
            return "0";
        }
        if (!findpath_helper(s, current->leftSubtree()).empty()) {
            return "0" + findpath_helper(s, current->leftSubtree());
        }
    } else if (current->rightSubtree() != nullptr && current->leftSubtree() == nullptr) {
        if (current->rightSubtree()->getstr() == s) {
            return "1";
        }
        if (!findpath_helper(s, current->rightSubtree()).empty()) {
            return "1" + findpath_helper(s, current->rightSubtree());
        }
    } else if (current->leftSubtree() != nullptr && current->rightSubtree() != nullptr) {
        if (current->leftSubtree()->getstr() == s) {
            return "0";
        }
        if (!findpath_helper(s, current->leftSubtree()).empty()) {
            return "0" + findpath_helper(s, current->leftSubtree());
        }
        if (current->rightSubtree()->getstr() == s) {
            return "1";
        }
        if (!findpath_helper(s, current->rightSubtree()).empty()) {
            return "1" + findpath_helper(s, current->rightSubtree());
        }
    }
    return "";
}


string BinaryTree::findPath(const string &s) const {
    if (root == nullptr) {
        return "-1";
    }
    if (root->getstr() == s) {
        return "";
    }
    string result = findpath_helper(s, root);;
    if (!result.empty()) {
        return result;
    } else {
        return "-1";
    }
}

int sum_helper(Node *current) {
    if (current == nullptr) {
        return 0;
    } else {
        return current->getnum() + sum_helper(current->leftSubtree()) + sum_helper(current->rightSubtree());
    }
}


int BinaryTree::sum() const {
    return sum_helper(root);
}

int depth_helper(Node *current) {
    if (current == nullptr) {
        return 0;
    } else if (depth_helper(current->leftSubtree()) > depth_helper(current->rightSubtree())) {
        return 1 + depth_helper(current->leftSubtree());
    } else {
        return 1 + depth_helper(current->rightSubtree());
    }
}

int BinaryTree::depth() const {
    return depth_helper(root);
}

void preorder_num_helper(Node *current) {
    if (current != nullptr) {
        cout << current->getnum() << " ";
        preorder_num_helper(current->leftSubtree());
        preorder_num_helper(current->rightSubtree());
    }
}

void BinaryTree::preorder_num() const {
    preorder_num_helper(root);
    cout << endl;
}

void inorder_str_helper(Node *current) {
    if (current != nullptr) {
        inorder_str_helper(current->leftSubtree());
        cout << current->getstr() << " ";
        inorder_str_helper(current->rightSubtree());
    }
}

void BinaryTree::inorder_str() const {
    inorder_str_helper(root);
    cout << endl;
}

void postorder_num_helper(Node *current) {
    if (current != nullptr) {
        postorder_num_helper(current->leftSubtree());
        postorder_num_helper(current->rightSubtree());
        cout << current->getnum() << " ";
    }
}

void BinaryTree::postorder_num() const {
    postorder_num_helper(root);
    cout << endl;
}

int allPathSumGreater_helper(Node *current) {
    if (current->leftSubtree() == nullptr || current->rightSubtree() == nullptr) {
        return current->getnum();
    } else {
        int left_sum = allPathSumGreater_helper(current->leftSubtree());
        int right_sum = allPathSumGreater_helper(current->rightSubtree());
        if (left_sum > right_sum) {
            return current->getnum() + right_sum;
        } else {}
        return current->getnum() + left_sum;
    }
}

bool BinaryTree::allPathSumGreater(int sum) const {
    int result = allPathSumGreater_helper(root);
    return result > sum;
}

bool covered_by_helper(Node *current, Node *test) {
    if (test == nullptr) {
        return false;
    }
    if (current->getnum() == test->getnum()) {
        if (current->leftSubtree() != nullptr && current->rightSubtree() == nullptr) {
            return covered_by_helper(current->leftSubtree(), test->leftSubtree());
        } else if (current->leftSubtree() == nullptr && current->rightSubtree() != nullptr) {
            return covered_by_helper(current->rightSubtree(), test->rightSubtree());
        } else if (current->leftSubtree() != nullptr && current->rightSubtree() != nullptr) {
            return covered_by_helper(current->rightSubtree(), test->rightSubtree())
                   && covered_by_helper(current->leftSubtree(), test->leftSubtree());
        } else {
            return true;
        }
    } else {
        return false;
    }
}

bool BinaryTree::covered_by(const BinaryTree &tree) const {
    if (root == nullptr) {
        return true;
    }
    if (tree.root == nullptr) {
        return false;
    }
    return covered_by_helper(root, tree.root);
}

bool contained_by_helper(Node *current, Node *test) {
    //cout<<current->getnum()<<" "<<test->getnum()<<endl;
    if (covered_by_helper(current, test)) {
        return true;
    }
    if (test->leftSubtree() != nullptr && test->rightSubtree() == nullptr) {
        return contained_by_helper(current, test->leftSubtree());
    } else if (test->leftSubtree() == nullptr && test->rightSubtree() != nullptr) {
        return contained_by_helper(current, test->rightSubtree());
    } else if (test->leftSubtree() != nullptr && test->rightSubtree() != nullptr) {
        return contained_by_helper(current, test->rightSubtree())
               || contained_by_helper(current, test->leftSubtree());
    } else {
        return false;
    }
}

bool BinaryTree::contained_by(const BinaryTree &tree) const {
    if (tree.root == nullptr) {
        return false;
    } else {
        return contained_by_helper(root, tree.root);
    }
}

void copy_helper(Node *current, Node *original_current) {
    //cout<<original_current->getstr()<<endl;
    if (original_current->leftSubtree() != nullptr) {
        Node *new_node = new Node(original_current->leftSubtree()->getstr(), original_current->leftSubtree()->getnum());
        current->setleft(new_node);
        copy_helper(current->leftSubtree(), original_current->leftSubtree());
    }
    if (original_current->rightSubtree() != nullptr) {
        Node *new_node = new Node(original_current->rightSubtree()->getstr(),
                                  original_current->rightSubtree()->getnum());
        current->setright(new_node);
        copy_helper(current->rightSubtree(), original_current->rightSubtree());
    }
}

BinaryTree BinaryTree::copy() const {
    Node *result_root = nullptr;
    if (root != nullptr) {
        result_root = new Node(root->getstr(), root->getnum());
        copy_helper(result_root, root);
    }
    return BinaryTree(result_root);
}
