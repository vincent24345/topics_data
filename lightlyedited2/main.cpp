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

    Node(int val) : key(val), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
private:
    Node* root;

    int getHeight(Node* node) {
        return node ? node->height : 0;
    }

    int getBalance(Node* node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

        return x;
    }

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

        return y;
    }

    Node* insert(Node* node, int key) {
        if (!node)
            return new Node(key);

        if (key < node->key)
            node->left = insert(node->left, key);
        else if (key > node->key)
            node->right = insert(node->right, key);
        else
            return node;

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));

        int balance = getBalance(node);

        // Balancing the tree
        if (balance > 1 && key < node->left->key)
            return rotateRight(node);

        if (balance < -1 && key > node->right->key)
            return rotateLeft(node);

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

    Node* getMinValueNode(Node* node) {
        Node* current = node;
        while (current && current->left != nullptr)
            current = current->left;
        return current;
    }

    Node* deleteNode(Node* root, int key) {
        if (!root)
            return root;

        if (key < root->key)
            root->left = deleteNode(root->left, key);
        else if (key > root->key)
            root->right = deleteNode(root->right, key);
        else {
            if (!root->left) {
                Node* temp = root->right;
                delete root;
                return temp;
            } else if (!root->right) {
                Node* temp = root->left;
                delete root;
                return temp;
            }

            Node* temp = getMinValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }

        if (!root)
            return root;

        root->height = 1 + max(getHeight(root->left), getHeight(root->right));

        int balance = getBalance(root);

        // Balancing the tree after deletion
        if (balance > 1 && getBalance(root->left) >= 0)
            return rotateRight(root);

        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }

        if (balance < -1 && getBalance(root->right) <= 0)
            return rotateLeft(root);

        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }

        return root;
    }

    void preOrder(Node* root) {
        if (!root)
            return;
        cout << root->key << " ";
        preOrder(root->left);
        preOrder(root->right);
    }

    void inOrder(Node* root) {
        if (!root)
            return;
        inOrder(root->left);
        cout << root->key << " ";
        inOrder(root->right);
    }

    void postOrder(Node* root) {
        if (!root)
            return;
        postOrder(root->left);
        postOrder(root->right);
        cout << root->key << " ";
    }

    void deleteTree(Node* node) {
        if (!node) return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }

public:
    AVLTree() : root(nullptr) {}

    ~AVLTree() {
        deleteTree(root);
    }

    void insert(int key) {
        root = insert(root, key);
    }

    void deleteNode(int key) {
        root = deleteNode(root, key);
    }

    void preOrder() {
        if (!root) {
            cout << "EMPTY" << endl;
            return;
        }
        preOrder(root);
        cout << endl;
    }

    void inOrder() {
        if (!root) {
            cout << "EMPTY" << endl;
            return;
        }
        inOrder(root);
        cout << endl;
    }

    void postOrder() {
        if (!root) {
            cout << "EMPTY" << endl;
            return;
        }
        postOrder(root);
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
    AVLTree tree;
    string input, cmd;
    getline(cin, input);
    stringstream ss(input);
    string finishCommand;

    while (ss >> cmd) {
        if (cmd == "PRE" || cmd == "IN" || cmd == "POST") {
            finishCommand = cmd;
            break;
        }

        if (!isValidCommand(cmd)) {
            cerr << "Invalid command: " << cmd << endl;
            continue;
        }

        if (cmd[0] == 'A') {
            tree.insert(stoi(cmd.substr(1)));
        } else if (cmd[0] == 'D') {
            tree.deleteNode(stoi(cmd.substr(1)));
        }
    }

    if (finishCommand == "PRE") {
        tree.preOrder();
    } else if (finishCommand == "IN") {
        tree.inOrder();
    } else if (finishCommand == "POST") {
        tree.postOrder();
    }

    return 0;
}
