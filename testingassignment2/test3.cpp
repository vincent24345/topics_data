#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
using namespace std;

class AVLNode {
public:
    int key;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(int val) : key(val), left(nullptr), right(nullptr), height(1) {}
};

class BalancedAVL {
private:
    AVLNode* root;

    int height(AVLNode* node) {
        return node ? node->height : 0;
    }

    int getBalanceFactor(AVLNode* node) {
        return node ? height(node->left) - height(node->right) : 0;
    }

    AVLNode* rotateRight(AVLNode* y) {
        AVLNode* x = y->left;
        y->left = x->right;
        x->right = y;
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;
        return x;
    }

    AVLNode* rotateLeft(AVLNode* x) {
        AVLNode* y = x->right;
        x->right = y->left;
        y->left = x;
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;
        return y;
    }

    AVLNode* insert(AVLNode* node, int key) {
        if (!node) return new AVLNode(key);
        if (key < node->key) node->left = insert(node->left, key);
        else if (key > node->key) node->right = insert(node->right, key);
        else return node;

        node->height = max(height(node->left), height(node->right)) + 1;
        int balance = getBalanceFactor(node);

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

    AVLNode* findMin(AVLNode* node) {
        while (node->left) node = node->left;
        return node;
    }

    AVLNode* remove(AVLNode* node, int key) {
        if (!node) return node;
        if (key < node->key) node->left = remove(node->left, key);
        else if (key > node->key) node->right = remove(node->right, key);
        else {
            if (!node->left || !node->right) {
                AVLNode* temp = node->left ? node->left : node->right;
                if (!temp) return nullptr;
                *node = *temp;
                delete temp;
            } else {
                AVLNode* temp = findMin(node->right);
                node->key = temp->key;
                node->right = remove(node->right, temp->key);
            }
        }

        node->height = max(height(node->left), height(node->right)) + 1;
        int balance = getBalanceFactor(node);

        if (balance > 1 && getBalanceFactor(node->left) >= 0) return rotateRight(node);
        if (balance > 1 && getBalanceFactor(node->left) < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (balance < -1 && getBalanceFactor(node->right) <= 0) return rotateLeft(node);
        if (balance < -1 && getBalanceFactor(node->right) > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    void preOrder(AVLNode* root) {
        if (root) {
            cout << root->key << " ";
            preOrder(root->left);
            preOrder(root->right);
        }
    }

    void inOrder(AVLNode* root) {
        if (root) {
            inOrder(root->left);
            cout << root->key << " ";
            inOrder(root->right);
        }
    }

    void postOrder(AVLNode* root) {
        if (root) {
            postOrder(root->left);
            postOrder(root->right);
            cout << root->key << " ";
        }
    }

public:
    BalancedAVL() : root(nullptr) {}

    void add(int key) {
        root = insert(root, key);
    }

    void del(int key) {
        root = remove(root, key);
    }

    void traverse(const string& order) {
        if (order == "PRE") preOrder(root);
        else if (order == "IN") inOrder(root);
        else if (order == "POST") postOrder(root);
        cout << endl;
    }
};

bool isValidCommand(const string& cmd) {
    if (cmd.empty()) return false;

    if (cmd[0] == 'A' || cmd[0] == 'D') {
        return cmd.size() > 1 && all_of(cmd.begin() + 1, cmd.end(), ::isdigit);
    }
    return cmd == "PRE" || cmd == "IN" || cmd == "POST";
}

int main() {
    BalancedAVL tree;
    string input;
    getline(cin, input);
    stringstream ss(input);
    string command;

    while (ss >> command) {
        if (command == "PRE" || command == "IN" || command == "POST") {
            tree.traverse(command);
            break;
        }
        if (!isValidCommand(command)) {
            cerr << "Invalid command: " << command << endl;
            continue;
        }
        if (command[0] == 'A') tree.add(stoi(command.substr(1)));
        else if (command[0] == 'D') tree.del(stoi(command.substr(1)));
    }
    return 0;
}
