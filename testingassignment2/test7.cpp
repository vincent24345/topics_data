#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
using namespace std;

class TreeNode {
public:
    int data;
    TreeNode* leftChild;
    TreeNode* rightChild;
    int height;
    TreeNode(int val) : data(val), leftChild(nullptr), rightChild(nullptr), height(1) {}
};

class AVLTreeSystem {
private:
    TreeNode* rootNode;

    int getNodeHeight(TreeNode* node) {
        return node ? node->height : 0;
    }

    TreeNode* balanceTree(TreeNode* node) {
        int balanceFactor = getNodeHeight(node->leftChild) - getNodeHeight(node->rightChild);
        if (balanceFactor > 1) {
            if (getNodeHeight(node->leftChild->leftChild) >= getNodeHeight(node->leftChild->rightChild))
                return rotateRight(node);
            else {
                node->leftChild = rotateLeft(node->leftChild);
                return rotateRight(node);
            }
        } else if (balanceFactor < -1) {
            if (getNodeHeight(node->rightChild->rightChild) >= getNodeHeight(node->rightChild->leftChild))
                return rotateLeft(node);
            else {
                node->rightChild = rotateRight(node->rightChild);
                return rotateLeft(node);
            }
        }
        return node;
    }

    TreeNode* rotateRight(TreeNode* y) {
        TreeNode* x = y->leftChild;
        y->leftChild = x->rightChild;
        x->rightChild = y;
        y->height = max(getNodeHeight(y->leftChild), getNodeHeight(y->rightChild)) + 1;
        x->height = max(getNodeHeight(x->leftChild), getNodeHeight(x->rightChild)) + 1;
        return x;
    }

    TreeNode* rotateLeft(TreeNode* x) {
        TreeNode* y = x->rightChild;
        x->rightChild = y->leftChild;
        y->leftChild = x;
        x->height = max(getNodeHeight(x->leftChild), getNodeHeight(x->rightChild)) + 1;
        y->height = max(getNodeHeight(y->leftChild), getNodeHeight(y->rightChild)) + 1;
        return y;
    }

    TreeNode* insertValue(TreeNode* node, int data) {
        if (!node) return new TreeNode(data);
        if (data < node->data)
            node->leftChild = insertValue(node->leftChild, data);
        else if (data > node->data)
            node->rightChild = insertValue(node->rightChild, data);
        else
            return node;

        node->height = 1 + max(getNodeHeight(node->leftChild), getNodeHeight(node->rightChild));
        return balanceTree(node);
    }

    TreeNode* deleteValue(TreeNode* node, int data) {
        if (!node) return node;
        if (data < node->data)
            node->leftChild = deleteValue(node->leftChild, data);
        else if (data > node->data)
            node->rightChild = deleteValue(node->rightChild, data);
        else {
            if (!node->leftChild || !node->rightChild) {
                TreeNode* temp = node->leftChild ? node->leftChild : node->rightChild;
                delete node;
                return temp;
            } else {
                TreeNode* temp = findMinNode(node->rightChild);
                node->data = temp->data;
                node->rightChild = deleteValue(node->rightChild, temp->data);
            }
        }
        node->height = 1 + max(getNodeHeight(node->leftChild), getNodeHeight(node->rightChild));
        return balanceTree(node);
    }

    TreeNode* findMinNode(TreeNode* node) {
        while (node->leftChild) node = node->leftChild;
        return node;
    }

    void inOrderTraversal(TreeNode* node) {
        if (node) {
            inOrderTraversal(node->leftChild);
            cout << node->data << " ";
            inOrderTraversal(node->rightChild);
        }
    }

    void preOrderTraversal(TreeNode* node) {
        if (node) {
            cout << node->data << " ";
            preOrderTraversal(node->leftChild);
            preOrderTraversal(node->rightChild);
        }
    }

    void postOrderTraversal(TreeNode* node) {
        if (node) {
            postOrderTraversal(node->leftChild);
            postOrderTraversal(node->rightChild);
            cout << node->data << " ";
        }
    }

public:
    AVLTreeSystem() : rootNode(nullptr) {}

    void insertNode(int value) {
        rootNode = insertValue(rootNode, value);
    }

    void deleteNode(int value) {
        rootNode = deleteValue(rootNode, value);
    }

    void displayTree(const string& order) {
        if (order == "IN") inOrderTraversal(rootNode);
        else if (order == "PRE") preOrderTraversal(rootNode);
        else if (order == "POST") postOrderTraversal(rootNode);
        cout << endl;
    }
};

bool checkCommand(const string& command) {
    if (command.empty()) return false;
    if (command[0] == 'A' || command[0] == 'D')
        return command.size() > 1 && all_of(command.begin() + 1, command.end(), ::isdigit);
    return command == "IN" || command == "PRE" || command == "POST";
}

int main() {
    AVLTreeSystem avlTree;
    string input;
    getline(cin, input);
    stringstream ss(input);
    string command;

    while (ss >> command) {
        if (command == "IN" || command == "PRE" || command == "POST") {
            avlTree.displayTree(command);
            break;
        }

        if (!checkCommand(command)) {
            cerr << "Invalid command: " << command << endl;
            continue;
        }

        if (command[0] == 'A') avlTree.insertNode(stoi(command.substr(1)));
        else if (command[0] == 'D') avlTree.deleteNode(stoi(command.substr(1)));
    }
    return 0;
}
