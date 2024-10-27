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
    int nodeHeight;

    Node(int value) : key(value), left(nullptr), right(nullptr), nodeHeight(1) {}
};

class AVLTreeStructure {
private:
    Node* root;

    int height(Node* node) {
        return node ? node->nodeHeight : 0;
    }

    int balanceFactor(Node* node) {
        return node ? height(node->left) - height(node->right) : 0;
    }

    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->nodeHeight = max(height(y->left), height(y->right)) + 1;
        x->nodeHeight = max(height(x->left), height(x->right)) + 1;

        return x;
    }

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->nodeHeight = max(height(x->left), height(x->right)) + 1;
        y->nodeHeight = max(height(y->left), height(y->right)) + 1;

        return y;
    }

    Node* insert(Node* node, int key) {
        if (!node) return new Node(key);

        if (key < node->key)
            node->left = insert(node->left, key);
        else if (key > node->key)
            node->right = insert(node->right, key);
        else
            return node;

        node->nodeHeight = 1 + max(height(node->left), height(node->right));

        int balance = balanceFactor(node);

        if (balance > 1 && key < node->left->key) return rotateRight(node);
        if (balance < -1 && key > node->right->key) return rotateLeft(node);
        if (balance > 1 && key > node->left->key) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (balance < -1 && key < node->right->key) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    Node* findMin(Node* node) {
        while (node->left) node = node->left;
        return node;
    }

    Node* deleteNode(Node* root, int key) {
        if (!root) return root;

        if (key < root->key) {
            root->left = deleteNode(root->left, key);
        } else if (key > root->key) {
            root->right = deleteNode(root->right, key);
        } else {
            if (!root->left || !root->right) {
                Node* temp = root->left ? root->left : root->right;
                delete root;
                return temp;
            }

            Node* temp = findMin(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }

        if (!root) return root;

        root->nodeHeight = 1 + max(height(root->left), height(root->right));
        int balance = balanceFactor(root);

        if (balance > 1 && balanceFactor(root->left) >= 0) return rotateRight(root);
        if (balance > 1 && balanceFactor(root->left) < 0) {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }
        if (balance < -1 && balanceFactor(root->right) <= 0) return rotateLeft(root);
        if (balance < -1 && balanceFactor(root->right) > 0) {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }

        return root;
    }

    void displayInOrder(Node* node) {
        if (node) {
            displayInOrder(node->left);
            cout << node->key << " ";
            displayInOrder(node->right);
        }
    }

    void displayPreOrder(Node* node) {
        if (node) {
            cout << node->key << " ";
            displayPreOrder(node->left);
            displayPreOrder(node->right);
        }
    }

    void displayPostOrder(Node* node) {
        if (node) {
            displayPostOrder(node->left);
            displayPostOrder(node->right);
            cout << node->key << " ";
        }
    }

public:
    AVLTreeStructure() : root(nullptr) {}

    void insertKey(int key) {
        root = insert(root, key);
    }

    void removeKey(int key) {
        root = deleteNode(root, key);
    }

    void traverseTree(const string& order) {
        if (order == "IN")
            displayInOrder(root);
        else if (order == "PRE")
            displayPreOrder(root);
        else if (order == "POST")
            displayPostOrder(root);
        cout << endl;
    }
};

bool isCommandValid(const string& command) {
    if (command.empty()) return false;

    if (command[0] == 'A' || command[0] == 'D') {
        if (command.length() > 1 && all_of(command.begin() + 1, command.end(), ::isdigit)) {
            int num = stoi(command.substr(1));
            return num >= 1 && num <= 100;
        }
        return false;
    }
    return command == "IN" || command == "PRE" || command == "POST";
}

int main() {
    AVLTreeStructure avl;
    string input;
    getline(cin, input);
    stringstream ss(input);
    string command;

    while (ss >> command) {
        if (command == "IN" || command == "PRE" || command == "POST") {
            avl.traverseTree(command);
            break;
        }

        if (!isCommandValid(command)) {
            cerr << "Invalid command: " << command << endl;
            continue;
        }

        if (command[0] == 'A') avl.insertKey(stoi(command.substr(1)));
        else if (command[0] == 'D') avl.removeKey(stoi(command.substr(1)));
    }
    return 0;
}
