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

class AVLTree {
private:
    AVLNode* root;

    int getHeight(AVLNode* node) {
        return node ? node->height : 0;
    }

    int getBalance(AVLNode* node) {
        return node ? getHeight(node->leftChild) - getHeight(node->rightChild) : 0;
    }

    AVLNode* rotateRight(AVLNode* y) {
        AVLNode* x = y->leftChild;
        AVLNode* T2 = x->rightChild;

        x->rightChild = y;
        y->leftChild = T2;

        y->height = max(getHeight(y->leftChild), getHeight(y->rightChild)) + 1;
        x->height = max(getHeight(x->leftChild), getHeight(x->rightChild)) + 1;

        return x;
    }

    AVLNode* rotateLeft(AVLNode* x) {
        AVLNode* y = x->rightChild;
        AVLNode* T2 = y->leftChild;

        y->leftChild = x;
        x->rightChild = T2;

        x->height = max(getHeight(x->leftChild), getHeight(x->rightChild)) + 1;
        y->height = max(getHeight(y->leftChild), getHeight(y->rightChild)) + 1;

        return y;
    }

    AVLNode* insert(AVLNode* node, int key) {
        if (!node)
            return new AVLNode(key);

        if (key < node->data)
            node->leftChild = insert(node->leftChild, key);
        else if (key > node->data)
            node->rightChild = insert(node->rightChild, key);
        else
            return node;

        node->height = 1 + max(getHeight(node->leftChild), getHeight(node->rightChild));

        int balance = getBalance(node);

        if (balance > 1 && key < node->leftChild->data)
            return rotateRight(node);

        if (balance < -1 && key > node->rightChild->data)
            return rotateLeft(node);

        if (balance > 1 && key > node->leftChild->data) {
            node->leftChild = rotateLeft(node->leftChild);
            return rotateRight(node);
        }

        if (balance < -1 && key < node->rightChild->data) {
            node->rightChild = rotateRight(node->rightChild);
            return rotateLeft(node);
        }

        return node;
    }

    AVLNode* findMin(AVLNode* node) {
        AVLNode* current = node;
        while (current && current->leftChild != nullptr)
            current = current->leftChild;
        return current;
    }

    AVLNode* remove(AVLNode* root, int key) {
        if (!root)
            return root;

        if (key < root->data)
            root->leftChild = remove(root->leftChild, key);
        else if (key > root->data)
            root->rightChild = remove(root->rightChild, key);
        else {
            if (!root->leftChild) {
                AVLNode* temp = root->rightChild;
                delete root;
                return temp;
            } else if (!root->rightChild) {
                AVLNode* temp = root->leftChild;
                delete root;
                return temp;
            }

            AVLNode* temp = findMin(root->rightChild);
            root->data = temp->data;
            root->rightChild = remove(root->rightChild, temp->data);
        }

        if (!root)
            return root;

        root->height = 1 + max(getHeight(root->leftChild), getHeight(root->rightChild));

        int balance = getBalance(root);

        if (balance > 1 && getBalance(root->leftChild) >= 0)
            return rotateRight(root);

        if (balance > 1 && getBalance(root->leftChild) < 0) {
            root->leftChild = rotateLeft(root->leftChild);
            return rotateRight(root);
        }

        if (balance < -1 && getBalance(root->rightChild) <= 0)
            return rotateLeft(root);

        if (balance < -1 && getBalance(root->rightChild) > 0) {
            root->rightChild = rotateRight(root->rightChild);
            return rotateLeft(root);
        }

        return root;
    }

    void traversePreOrder(AVLNode* root) {
        if (!root)
            return;
        cout << root->data << " ";
        traversePreOrder(root->leftChild);
        traversePreOrder(root->rightChild);
    }

    void traverseInOrder(AVLNode* root) {
        if (!root)
            return;
        traverseInOrder(root->leftChild);
        cout << root->data << " ";
        traverseInOrder(root->rightChild);
    }

    void traversePostOrder(AVLNode* root) {
        if (!root)
            return;
        traversePostOrder(root->leftChild);
        traversePostOrder(root->rightChild);
        cout << root->data << " ";
    }

    void clear(AVLNode* node) {
        if (!node) return;
        clear(node->leftChild);
        clear(node->rightChild);
        delete node;
    }

public:
    AVLTree() : root(nullptr) {}

    ~AVLTree() {
        clear(root);
    }

    void insert(int key) {
        root = insert(root, key);
    }

    void deleteNode(int key) {
        root = remove(root, key);
    }

    void preOrderTraversal() {
        if (!root) {
            cout << "EMPTY" << endl;
            return;
        }
        traversePreOrder(root);
        cout << endl;
    }

    void inOrderTraversal() {
        if (!root) {
            cout << "EMPTY" << endl;
            return;
        }
        traverseInOrder(root);
        cout << endl;
    }

    void postOrderTraversal() {
        if (!root) {
            cout << "EMPTY" << endl;
            return;
        }
        traversePostOrder(root);
        cout << endl;
    }
};

bool validateCmd(const string& cmd) {
    if (cmd.empty()) return false;

    if (cmd[0] == 'A' || cmd[0] == 'D') {
        if (cmd.length() > 1 && all_of(cmd.begin() + 1, cmd.end(), ::isdigit)) {
            int num = stoi(cmd.substr(1));
            return num >= 1 && num <= 100;
        }
        return false;
    }
    return cmd == "PRE" || cmd == "IN" || cmd == "POST";
}

int main() {
    AVLTree avlTree;
    string input, cmd;
    getline(cin, input);
    stringstream ss(input);
    string finishCmd;

    while (ss >> cmd) {
        if (cmd == "PRE" || cmd == "IN" || cmd == "POST") {
            finishCmd = cmd;
            break;
        }

        if (!validateCmd(cmd)) {
            cerr << "Invalid command: " << cmd << endl;
            continue;
        }

        if (cmd[0] == 'A') {
            avlTree.insert(stoi(cmd.substr(1)));
        } else if (cmd[0] == 'D') {
            avlTree.deleteNode(stoi(cmd.substr(1)));
        }
    }

    if (finishCmd == "PRE") {
        avlTree.preOrderTraversal();
    } else if (finishCmd == "IN") {
        avlTree.inOrderTraversal();
    } else if (finishCmd == "POST") {
        avlTree.postOrderTraversal();
    }

    return 0;
}
