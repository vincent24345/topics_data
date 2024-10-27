#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
using namespace std;

class AVLNode {
public:
    int value;
    AVLNode* leftChild;
    AVLNode* rightChild;
    int height;

    AVLNode(int val) : value(val), leftChild(nullptr), rightChild(nullptr), height(1) {}
};

class AVLTree {
private:
    AVLNode* rootNode;

    int getNodeHeight(AVLNode* node) {
        return node ? node->height : 0;
    }

    int getNodeBalance(AVLNode* node) {
        return node ? getNodeHeight(node->leftChild) - getNodeHeight(node->rightChild) : 0;
    }

    AVLNode* rightRotate(AVLNode* y) {
        AVLNode* x = y->leftChild;
        AVLNode* T2 = x->rightChild;

        x->rightChild = y;
        y->leftChild = T2;

        y->height = max(getNodeHeight(y->leftChild), getNodeHeight(y->rightChild)) + 1;
        x->height = max(getNodeHeight(x->leftChild), getNodeHeight(x->rightChild)) + 1;

        return x;
    }

    AVLNode* leftRotate(AVLNode* x) {
        AVLNode* y = x->rightChild;
        AVLNode* T2 = y->leftChild;

        y->leftChild = x;
        x->rightChild = T2;

        x->height = max(getNodeHeight(x->leftChild), getNodeHeight(x->rightChild)) + 1;
        y->height = max(getNodeHeight(y->leftChild), getNodeHeight(y->rightChild)) + 1;

        return y;
    }

    AVLNode* insertNode(AVLNode* node, int key) {
        if (!node)
            return new AVLNode(key);

        if (key < node->value)
            node->leftChild = insertNode(node->leftChild, key);
        else if (key > node->value)
            node->rightChild = insertNode(node->rightChild, key);
        else
            return node;

        node->height = 1 + max(getNodeHeight(node->leftChild), getNodeHeight(node->rightChild));

        int balanceFactor = getNodeBalance(node);

        if (balanceFactor > 1 && key < node->leftChild->value)
            return rightRotate(node);

        if (balanceFactor < -1 && key > node->rightChild->value)
            return leftRotate(node);

        if (balanceFactor > 1 && key > node->leftChild->value) {
            node->leftChild = leftRotate(node->leftChild);
            return rightRotate(node);
        }

        if (balanceFactor < -1 && key < node->rightChild->value) {
            node->rightChild = rightRotate(node->rightChild);
            return leftRotate(node);
        }

        return node;
    }

    AVLNode* findMinimum(AVLNode* node) {
        AVLNode* current = node;
        while (current && current->leftChild != nullptr)
            current = current->leftChild;
        return current;
    }

    AVLNode* removeNode(AVLNode* root, int key) {
        if (!root)
            return root;

        if (key < root->value)
            root->leftChild = removeNode(root->leftChild, key);
        else if (key > root->value)
            root->rightChild = removeNode(root->rightChild, key);
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

            AVLNode* temp = findMinimum(root->rightChild);
            root->value = temp->value;
            root->rightChild = removeNode(root->rightChild, temp->value);
        }

        if (!root)
            return root;

        root->height = 1 + max(getNodeHeight(root->leftChild), getNodeHeight(root->rightChild));

        int balanceFactor = getNodeBalance(root);

        if (balanceFactor > 1 && getNodeBalance(root->leftChild) >= 0)
            return rightRotate(root);

        if (balanceFactor > 1 && getNodeBalance(root->leftChild) < 0) {
            root->leftChild = leftRotate(root->leftChild);
            return rightRotate(root);
        }

        if (balanceFactor < -1 && getNodeBalance(root->rightChild) <= 0)
            return leftRotate(root);

        if (balanceFactor < -1 && getNodeBalance(root->rightChild) > 0) {
            root->rightChild = rightRotate(root->rightChild);
            return leftRotate(root);
        }

        return root;
    }

    void preOrderTraversal(AVLNode* root) {
        if (!root)
            return;
        cout << root->value << " ";
        preOrderTraversal(root->leftChild);
        preOrderTraversal(root->rightChild);
    }

    void inOrderTraversal(AVLNode* root) {
        if (!root)
            return;
        inOrderTraversal(root->leftChild);
        cout << root->value << " ";
        inOrderTraversal(root->rightChild);
    }

    void postOrderTraversal(AVLNode* root) {
        if (!root)
            return;
        postOrderTraversal(root->leftChild);
        postOrderTraversal(root->rightChild);
        cout << root->value << " ";
    }

    void clear(AVLNode* node) {
        if (!node) return;
        clear(node->leftChild);
        clear(node->rightChild);
        delete node;
    }

public:
    AVLTree() : rootNode(nullptr) {}

    ~AVLTree() {
        clear(rootNode);
    }

    void insert(int key) {
        rootNode = insertNode(rootNode, key);
    }

    void remove(int key) {
        rootNode = removeNode(rootNode, key);
    }

    void preOrder() {
        if (!rootNode) {
            cout << "EMPTY" << endl;
            return;
        }
        preOrderTraversal(rootNode);
        cout << endl;
    }

    void inOrder() {
        if (!rootNode) {
            cout << "EMPTY" << endl;
            return;
        }
        inOrderTraversal(rootNode);
        cout << endl;
    }

    void postOrder() {
        if (!rootNode) {
            cout << "EMPTY" << endl;
            return;
        }
        postOrderTraversal(rootNode);
        cout << endl;
    }
};

bool isValidCommand(const string& cmd) {
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
    AVLTree avl;
    string input, command;
    getline(cin, input);
    stringstream ss(input);
    string lastCommand;

    while (ss >> command) {
        if (command == "PRE" || command == "IN" || command == "POST") {
            lastCommand = command;
            break;
        }

        if (!isValidCommand(command)) {
            cerr << "Invalid command: " << command << endl;
            continue;
        }

        if (command[0] == 'A') {
            avl.insert(stoi(command.substr(1)));
        } else if (command[0] == 'D') {
            avl.remove(stoi(command.substr(1)));
        }
    }

    if (lastCommand == "PRE") {
        avl.preOrder();
    } else if (lastCommand == "IN") {
        avl.inOrder();
    } else if (lastCommand == "POST") {
        avl.postOrder();
    }

    return 0;
}
