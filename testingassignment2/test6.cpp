#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
using namespace std;

class Node {
public:
    int key;
    Node* left;
    Node* right;
    int height;
    Node(int value) : key(value), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
private:
    Node* root;

    int getHeight(Node* node) {
        return node ? node->height : 0;
    }

    int getBalanceFactor(Node* node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    Node* rotateRight(Node* y) {
        Node* x = y->left;
        y->left = x->right;
        x->right = y;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        return x;
    }

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        y->left = x;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        return y;
    }

    Node* rebalance(Node* node, int key) {
        int balance = getBalanceFactor(node);
        if (balance > 1) {
            if (key < node->left->key)
                return rotateRight(node);
            else {
                node->left = rotateLeft(node->left);
                return rotateRight(node);
            }
        }
        if (balance < -1) {
            if (key > node->right->key)
                return rotateLeft(node);
            else {
                node->right = rotateRight(node->right);
                return rotateLeft(node);
            }
        }
        return node;
    }

    Node* insertHelper(Node* node, int key) {
        if (!node) return new Node(key);
        if (key < node->key)
            node->left = insertHelper(node->left, key);
        else if (key > node->key)
            node->right = insertHelper(node->right, key);
        else
            return node;

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        return rebalance(node, key);
    }

    Node* findMinNode(Node* node) {
        return node->left ? findMinNode(node->left) : node;
    }

    Node* deleteHelper(Node* node, int key) {
        if (!node) return node;
        if (key < node->key)
            node->left = deleteHelper(node->left, key);
        else if (key > node->key)
            node->right = deleteHelper(node->right, key);
        else {
            if (!node->left || !node->right) {
                Node* temp = node->left ? node->left : node->right;
                delete node;
                return temp;
            } else {
                Node* temp = findMinNode(node->right);
                node->key = temp->key;
                node->right = deleteHelper(node->right, temp->key);
            }
        }
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        return rebalance(node, key);
    }

    void printInOrder(Node* node) {
        if (node) {
            printInOrder(node->left);
            cout << node->key << " ";
            printInOrder(node->right);
        }
    }

    void printPreOrder(Node* node) {
        if (node) {
            cout << node->key << " ";
            printPreOrder(node->left);
            printPreOrder(node->right);
        }
    }

    void printPostOrder(Node* node) {
        if (node) {
            printPostOrder(node->left);
            printPostOrder(node->right);
            cout << node->key << " ";
        }
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(int key) {
        root = insertHelper(root, key);
    }

    void remove(int key) {
        root = deleteHelper(root, key);
    }

    void traverse(const string& order) {
        if (order == "IN") {
            printInOrder(root);
        } else if (order == "PRE") {
            printPreOrder(root);
        } else if (order == "POST") {
            printPostOrder(root);
        }
        cout << endl;
    }
};

bool isValidCommand(const string& command) {
    if (command.empty()) return false;
    if (command[0] == 'A' || command[0] == 'D') {
        return command.size() > 1 && all_of(command.begin() + 1, command.end(), ::isdigit);
    }
    return command == "IN" || command == "PRE" || command == "POST";
}

int main() {
    AVLTree avl;
    string input;
    getline(cin, input);
    stringstream ss(input);
    string command;

    while (ss >> command) {
        if (command == "IN" || command == "PRE" || command == "POST") {
            avl.traverse(command);
            break;
        }
        if (!isValidCommand(command)) {
            cerr << "Invalid command: " << command << endl;
            continue;
        }
        if (command[0] == 'A') avl.insert(stoi(command.substr(1)));
        else if (command[0] == 'D') avl.remove(stoi(command.substr(1)));
    }
    return 0;
}
