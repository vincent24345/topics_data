#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
using namespace std;

class AVLTreeNode {
public:
    int key;
    AVLTreeNode* left;
    AVLTreeNode* right;
    int height;

    AVLTreeNode(int val) : key(val), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
private:
    AVLTreeNode* rootNode;

    int height(AVLTreeNode* node) {
        return node ? node->height : 0;
    }

    int balance(AVLTreeNode* node) {
        return node ? height(node->left) - height(node->right) : 0;
    }

    AVLTreeNode* rightRotation(AVLTreeNode* y) {
        AVLTreeNode* x = y->left;
        AVLTreeNode* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        return x;
    }

    AVLTreeNode* leftRotation(AVLTreeNode* x) {
        AVLTreeNode* y = x->right;
        AVLTreeNode* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        return y;
    }

    AVLTreeNode* insertNode(AVLTreeNode* node, int key) {
        if (!node)
            return new AVLTreeNode(key);

        if (key < node->key)
            node->left = insertNode(node->left, key);
        else if (key > node->key)
            node->right = insertNode(node->right, key);
        else
            return node;

        node->height = 1 + max(height(node->left), height(node->right));

        int balanceFactor = balance(node);

        if (balanceFactor > 1 && key < node->left->key)
            return rightRotation(node);

        if (balanceFactor < -1 && key > node->right->key)
            return leftRotation(node);

        if (balanceFactor > 1 && key > node->left->key) {
            node->left = leftRotation(node->left);
            return rightRotation(node);
        }

        if (balanceFactor < -1 && key < node->right->key) {
            node->right = rightRotation(node->right);
            return leftRotation(node);
        }

        return node;
    }

    AVLTreeNode* minValueNode(AVLTreeNode* node) {
        AVLTreeNode* current = node;
        while (current && current->left != nullptr)
            current = current->left;
        return current;
    }

    AVLTreeNode* deleteNode(AVLTreeNode* root, int key) {
        if (!root)
            return root;

        if (key < root->key)
            root->left = deleteNode(root->left, key);
        else if (key > root->key)
            root->right = deleteNode(root->right, key);
        else {
            if (!root->left) {
                AVLTreeNode* temp = root->right;
                delete root;
                return temp;
            } else if (!root->right) {
                AVLTreeNode* temp = root->left;
                delete root;
                return temp;
            }

            AVLTreeNode* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }

        if (!root)
            return root;

        root->height = 1 + max(height(root->left), height(root->right));

        int balanceFactor = balance(root);

        if (balanceFactor > 1 && balance(root->left) >= 0)
            return rightRotation(root);

        if (balanceFactor > 1 && balance(root->left) < 0) {
            root->left = leftRotation(root->left);
            return rightRotation(root);
        }

        if (balanceFactor < -1 && balance(root->right) <= 0)
            return leftRotation(root);

        if (balanceFactor < -1 && balance(root->right) > 0) {
            root->right = rightRotation(root->right);
            return leftRotation(root);
        }

        return root;
    }

    void preOrderTraversal(AVLTreeNode* root) {
        if (!root)
            return;
        cout << root->key << " ";
        preOrderTraversal(root->left);
        preOrderTraversal(root->right);
    }

    void inOrderTraversal(AVLTreeNode* root) {
        if (!root)
            return;
        inOrderTraversal(root->left);
        cout << root->key << " ";
        inOrderTraversal(root->right);
    }

    void postOrderTraversal(AVLTreeNode* root) {
        if (!root)
            return;
        postOrderTraversal(root->left);
        postOrderTraversal(root->right);
        cout << root->key << " ";
    }

    void clear(AVLTreeNode* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
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

    void removeNode(int key) {
        rootNode = deleteNode(rootNode, key);
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

bool isCommandValid(const string& cmd) {
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
    string input, cmd;
    getline(cin, input);
    stringstream ss(input);
    string commandEnd;

    while (ss >> cmd) {
        if (cmd == "PRE" || cmd == "IN" || cmd == "POST") {
            commandEnd = cmd;
            break;
        }

        if (!isCommandValid(cmd)) {
            cerr << "Invalid command: " << cmd << endl;
            continue;
        }

        if (cmd[0] == 'A') {
            avl.insert(stoi(cmd.substr(1)));
        } else if (cmd[0] == 'D') {
            avl.removeNode(stoi(cmd.substr(1)));
        }
    }

    if (commandEnd == "PRE") {
        avl.preOrder();
    } else if (commandEnd == "IN") {
        avl.inOrder();
    } else if (commandEnd == "POST") {
        avl.postOrder();
    }

    return 0;
}
