#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
using namespace std;

class AVLNode {
public:
    int data;
    AVLNode* leftChild;
    AVLNode* rightChild;
    int height;

    AVLNode(int val) : data(val), leftChild(nullptr), rightChild(nullptr), height(1) {}
};

class AVLTreeManager {
private:
    AVLNode* root;

    int heightOfNode(AVLNode* node) {
        return node ? node->height : 0;
    }

    int getBalanceFactor(AVLNode* node) {
        return node ? heightOfNode(node->leftChild) - heightOfNode(node->rightChild) : 0;
    }

    AVLNode* rightRotate(AVLNode* y) {
        AVLNode* x = y->leftChild;
        AVLNode* T2 = x->rightChild;

        x->rightChild = y;
        y->leftChild = T2;

        y->height = max(heightOfNode(y->leftChild), heightOfNode(y->rightChild)) + 1;
        x->height = max(heightOfNode(x->leftChild), heightOfNode(x->rightChild)) + 1;

        return x;
    }

    AVLNode* leftRotate(AVLNode* x) {
        AVLNode* y = x->rightChild;
        AVLNode* T2 = y->leftChild;

        y->leftChild = x;
        x->rightChild = T2;

        x->height = max(heightOfNode(x->leftChild), heightOfNode(x->rightChild)) + 1;
        y->height = max(heightOfNode(y->leftChild), heightOfNode(y->rightChild)) + 1;

        return y;
    }

    AVLNode* addNode(AVLNode* node, int data) {
        if (!node)
            return new AVLNode(data);

        if (data < node->data)
            node->leftChild = addNode(node->leftChild, data);
        else if (data > node->data)
            node->rightChild = addNode(node->rightChild, data);
        else
            return node;

        node->height = 1 + max(heightOfNode(node->leftChild), heightOfNode(node->rightChild));

        int balance = getBalanceFactor(node);

        if (balance > 1 && data < node->leftChild->data)
            return rightRotate(node);

        if (balance < -1 && data > node->rightChild->data)
            return leftRotate(node);

        if (balance > 1 && data > node->leftChild->data) {
            node->leftChild = leftRotate(node->leftChild);
            return rightRotate(node);
        }

        if (balance < -1 && data < node->rightChild->data) {
            node->rightChild = rightRotate(node->rightChild);
            return leftRotate(node);
        }

        return node;
    }

    AVLNode* minValueNode(AVLNode* node) {
        AVLNode* current = node;
        while (current->leftChild != nullptr)
            current = current->leftChild;
        return current;
    }

    AVLNode* removeNode(AVLNode* root, int data) {
        if (!root)
            return root;

        if (data < root->data)
            root->leftChild = removeNode(root->leftChild, data);
        else if (data > root->data)
            root->rightChild = removeNode(root->rightChild, data);
        else {
            if (!root->leftChild || !root->rightChild) {
                AVLNode* temp = root->leftChild ? root->leftChild : root->rightChild;
                delete root;
                return temp;
            }

            AVLNode* temp = minValueNode(root->rightChild);
            root->data = temp->data;
            root->rightChild = removeNode(root->rightChild, temp->data);
        }

        if (!root)
            return root;

        root->height = 1 + max(heightOfNode(root->leftChild), heightOfNode(root->rightChild));

        int balance = getBalanceFactor(root);

        if (balance > 1 && getBalanceFactor(root->leftChild) >= 0)
            return rightRotate(root);

        if (balance > 1 && getBalanceFactor(root->leftChild) < 0) {
            root->leftChild = leftRotate(root->leftChild);
            return rightRotate(root);
        }

        if (balance < -1 && getBalanceFactor(root->rightChild) <= 0)
            return leftRotate(root);

        if (balance < -1 && getBalanceFactor(root->rightChild) > 0) {
            root->rightChild = rightRotate(root->rightChild);
            return leftRotate(root);
        }

        return root;
    }

    void displayPreOrder(AVLNode* root) {
        if (root) {
            cout << root->data << " ";
            displayPreOrder(root->leftChild);
            displayPreOrder(root->rightChild);
        }
    }

    void displayInOrder(AVLNode* root) {
        if (root) {
            displayInOrder(root->leftChild);
            cout << root->data << " ";
            displayInOrder(root->rightChild);
        }
    }

    void displayPostOrder(AVLNode* root) {
        if (root) {
            displayPostOrder(root->leftChild);
            displayPostOrder(root->rightChild);
            cout << root->data << " ";
        }
    }

    void clearTree(AVLNode* node) {
        if (node) {
            clearTree(node->leftChild);
            clearTree(node->rightChild);
            delete node;
        }
    }

public:
    AVLTreeManager() : root(nullptr) {}

    ~AVLTreeManager() {
        clearTree(root);
    }

    void add(int data) {
        root = addNode(root, data);
    }

    void remove(int data) {
        root = removeNode(root, data);
    }

    void printPreOrder() {
        cout << "Pre-order traversal: ";
        if (!root)
            cout << "Tree is empty" << endl;
        else {
            displayPreOrder(root);
            cout << endl;
        }
    }

    void printInOrder() {
        cout << "In-order traversal: ";
        if (!root)
            cout << "Tree is empty" << endl;
        else {
            displayInOrder(root);
            cout << endl;
        }
    }

    void printPostOrder() {
        cout << "Post-order traversal: ";
        if (!root)
            cout << "Tree is empty" << endl;
        else {
            displayPostOrder(root);
            cout << endl;
        }
    }
};

bool validateCommand(const string& command) {
    if (command.empty()) return false;

    if (command[0] == 'A' || command[0] == 'D') {
        if (command.length() > 1 && all_of(command.begin() + 1, command.end(), ::isdigit)) {
            int num = stoi(command.substr(1));
            return num >= 1 && num <= 100;
        }
        return false;
    }
    return command == "PRE" || command == "IN" || command == "POST";
}

int main() {
    AVLTreeManager avlTree;
    string input, cmd;
    getline(cin, input);
    stringstream ss(input);
    string finalCommand;

    while (ss >> cmd) {
        if (cmd == "PRE" || cmd == "IN" || cmd == "POST") {
            finalCommand = cmd;
            break;
        }

        if (!validateCommand(cmd)) {
            cerr << "Invalid command: " << cmd << endl;
            continue;
        }

        if (cmd[0] == 'A') {
            avlTree.add(stoi(cmd.substr(1)));
        } else if (cmd[0] == 'D') {
            avlTree.remove(stoi(cmd.substr(1)));
        }
    }

    if (finalCommand == "PRE") {
        avlTree.printPreOrder();
    } else if (finalCommand == "IN") {
        avlTree.printInOrder();
    } else if (finalCommand == "POST") {
        avlTree.printPostOrder();
    }

    return 0;
}
