#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
using namespace std;

struct AVLNode {
    int key;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(int value) : key(value), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
private:
    AVLNode* root;

    int getHeight(AVLNode* node) {
        return node ? node->height : 0;
    }

    int getBalanceFactor(AVLNode* node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    AVLNode* rightRotate(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

        return x;
    }

    AVLNode* leftRotate(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

        return y;
    }

    AVLNode* insertNode(AVLNode* node, int key) {
        if (!node) return new AVLNode(key);

        if (key < node->key)
            node->left = insertNode(node->left, key);
        else if (key > node->key)
            node->right = insertNode(node->right, key);
        else
            return node;

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));

        int balance = getBalanceFactor(node);

        if (balance > 1 && key < node->left->key)
            return rightRotate(node);

        if (balance < -1 && key > node->right->key)
            return leftRotate(node);

        if (balance > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    AVLNode* minValueNode(AVLNode* node) {
        while (node->left) {
            node = node->left;
        }
        return node;
    }

    AVLNode* removeNode(AVLNode* root, int key) {
        if (!root) return root;

        if (key < root->key)
            root->left = removeNode(root->left, key);
        else if (key > root->key)
            root->right = removeNode(root->right, key);
        else {
            if (!root->left) {
                AVLNode* temp = root->right;
                delete root;
                return temp;
            } else if (!root->right) {
                AVLNode* temp = root->left;
                delete root;
                return temp;
            }

            AVLNode* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = removeNode(root->right, temp->key);
        }

        if (!root) return root;

        root->height = 1 + max(getHeight(root->left), getHeight(root->right));

        int balance = getBalanceFactor(root);

        if (balance > 1 && getBalanceFactor(root->left) >= 0)
            return rightRotate(root);

        if (balance < -1 && getBalanceFactor(root->right) <= 0)
            return leftRotate(root);

        if (balance > 1 && getBalanceFactor(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        if (balance < -1 && getBalanceFactor(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    void preOrderTraversal(AVLNode* node) {
        if (node) {
            cout << node->key << " ";
            preOrderTraversal(node->left);
            preOrderTraversal(node->right);
        }
    }

    void inOrderTraversal(AVLNode* node) {
        if (node) {
            inOrderTraversal(node->left);
            cout << node->key << " ";
            inOrderTraversal(node->right);
        }
    }

    void postOrderTraversal(AVLNode* node) {
        if (node) {
            postOrderTraversal(node->left);
            postOrderTraversal(node->right);
            cout << node->key << " ";
        }
    }

    void clearTree(AVLNode* node) {
        if (node) {
            clearTree(node->left);
            clearTree(node->right);
            delete node;
        }
    }

public:
    AVLTree() : root(nullptr) {}

    ~AVLTree() {
        clearTree(root);
    }

    void insert(int key) {
        root = insertNode(root, key);
    }

    void remove(int key) {
        root = removeNode(root, key);
    }

    void preOrder() {
        if (!root) {
            cout << "EMPTY" << endl;
            return;
        }
        preOrderTraversal(root);
        cout << endl;
    }

    void inOrder() {
        if (!root) {
            cout << "EMPTY" << endl;
            return;
        }
        inOrderTraversal(root);
        cout << endl;
    }

    void postOrder() {
        if (!root) {
            cout << "EMPTY" << endl;
            return;
        }
        postOrderTraversal(root);
        cout << endl;
    }
};

bool isValidInput(const string& command) {
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
    AVLTree avl;
    string input;
    getline(cin, input);
    stringstream ss(input);
    string command;

    while (ss >> command) {
        if (command == "PRE" || command == "IN" || command == "POST") {
            break;
        }

        if (!isValidInput(command)) {
            cerr << "Invalid command: " << command << endl;
            continue;
        }

        if (command[0] == 'A') {
            avl.insert(stoi(command.substr(1)));
        } else if (command[0] == 'D') {
            avl.remove(stoi(command.substr(1)));
        }
    }

    if (command == "PRE") {
        avl.preOrder();
    } else if (command == "IN") {
        avl.inOrder();
    } else if (command == "POST") {
        avl.postOrder();
    }

    return 0;
}
