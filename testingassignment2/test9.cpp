#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
using namespace std;

class Node {
public:
    int key;
    Node* left;
    Node* right;
    int height;
    Node(int val) : key(val), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
private:
    Node* root;

    int height(Node* node) {
        return node ? node->height : 0;
    }

    int balanceFactor(Node* node) {
        return height(node->left) - height(node->right);
    }

    void updateHeight(Node* node) {
        node->height = 1 + max(height(node->left), height(node->right));
    }

    Node* rotateRight(Node* y) {
        Node* x = y->left;
        y->left = x->right;
        x->right = y;
        updateHeight(y);
        updateHeight(x);
        return x;
    }

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        y->left = x;
        updateHeight(x);
        updateHeight(y);
        return y;
    }

    Node* balance(Node* node) {
        int balance = balanceFactor(node);
        if (balance > 1) {
            if (balanceFactor(node->left) < 0)
                node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (balance < -1) {
            if (balanceFactor(node->right) > 0)
                node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        return node;
    }

    Node* insertHelper(Node* node, int key) {
        if (!node) return new Node(key);
        if (key < node->key)
            node->left = insertHelper(node->left, key);
        else if (key > node->key)
            node->right = insertHelper(node->right, key);

        updateHeight(node);
        return balance(node);
    }

    Node* deleteHelper(Node* node, int key) {
        if (!node) return nullptr;
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
        updateHeight(node);
        return balance(node);
    }

    Node* findMinNode(Node* node) {
        while (node->left) node = node->left;
        return node;
    }

    void inOrderTraversal(Node* node) {
        if (node) {
            inOrderTraversal(node->left);
            cout << node->key << " ";
            inOrderTraversal(node->right);
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

    void inOrder() {
        inOrderTraversal(root);
        cout << endl;
    }
};

bool validateCommand(const string& command) {
    if (command.empty()) return false;
    if (command[0] == 'A' || command[0] == 'D')
        return command.size() > 1 && all_of(command.begin() + 1, command.end(), ::isdigit);
    return command == "IN";
}

int main() {
    AVLTree tree;
    string input;
    getline(cin, input);
    stringstream ss(input);
    string command;

    while (ss >> command) {
        if (command == "IN") {
            tree.inOrder();
            break;
        }

        if (!validateCommand(command)) {
            cerr << "Invalid command: " << command << endl;
            continue;
        }

        if (command[0] == 'A') tree.insert(stoi(command.substr(1)));
        else if (command[0] == 'D') tree.remove(stoi(command.substr(1)));
    }
    return 0;
}
