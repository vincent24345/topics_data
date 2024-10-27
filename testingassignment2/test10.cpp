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

    int height(Node* node) {
        return node ? node->height : 0;
    }

    int getBalance(Node* node) {
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
        int balance = getBalance(node);
        if (balance > 1) {
            if (getBalance(node->left) < 0)
                node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (balance < -1) {
            if (getBalance(node->right) > 0)
                node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        return node;
    }

    Node* insertNode(Node* node, int key) {
        if (!node) return new Node(key);
        if (key < node->key)
            node->left = insertNode(node->left, key);
        else if (key > node->key)
            node->right = insertNode(node->right, key);
        else {
            cerr << "Duplicate key: " << key << endl; // Reject duplicates
            return node;
        }

        updateHeight(node);
        return balance(node);
    }

    Node* deleteNode(Node* node, int key) {
        if (!node) return nullptr;
        if (key < node->key)
            node->left = deleteNode(node->left, key);
        else if (key > node->key)
            node->right = deleteNode(node->right, key);
        else {
            if (!node->left || !node->right) {
                Node* temp = node->left ? node->left : node->right;
                delete node;
                return temp;
            } else {
                Node* successor = findMin(node->right);
                node->key = successor->key;
                node->right = deleteNode(node->right, successor->key);
            }
        }

        updateHeight(node);
        return balance(node);
    }

    Node* findMin(Node* node) {
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
        root = insertNode(root, key);
    }

    void remove(int key) {
        root = deleteNode(root, key);
    }

    void inOrder() {
        inOrderTraversal(root);
        cout << endl;
    }
};

bool isValidCommand(const string& command) {
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

        if (!isValidCommand(command)) {
            cerr << "Invalid command: " << command << endl;
            continue;
        }

        if (command[0] == 'A') tree.insert(stoi(command.substr(1)));
        else if (command[0] == 'D') tree.remove(stoi(command.substr(1)));
    }
    return 0;
}
