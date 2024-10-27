#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
using namespace std;

struct AVLTreeNode {
    int key;
    AVLTreeNode* left;
    AVLTreeNode* right;
    int height;

    AVLTreeNode(int value) : key(value), left(nullptr), right(nullptr), height(1) {}
};

class AVL {
private:
    AVLTreeNode* root;

    int getHeight(AVLTreeNode* node) {
        return node ? node->height : 0;
    }

    int getBalance(AVLTreeNode* node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    AVLTreeNode* rightRotate(AVLTreeNode* y) {
        AVLTreeNode* x = y->left;
        AVLTreeNode* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

        return x;
    }

    AVLTreeNode* leftRotate(AVLTreeNode* x) {
        AVLTreeNode* y = x->right;
        AVLTreeNode* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

        return y;
    }

    AVLTreeNode* insert(AVLTreeNode* node, int key) {
        if (!node) return new AVLTreeNode(key);

        if (key < node->key)
            node->left = insert(node->left, key);
        else if (key > node->key)
            node->right = insert(node->right, key);
        else
            return node;

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));

        int balance = getBalance(node);

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

    AVLTreeNode* minValueNode(AVLTreeNode* node) {
        while (node->left) {
            node = node->left;
        }
        return node;
    }

    AVLTreeNode* remove(AVLTreeNode* root, int key) {
        if (!root) return root;

        if (key < root->key)
            root->left = remove(root->left, key);
        else if (key > root->key)
            root->right = remove(root->right, key);
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
            root->right = remove(root->right, temp->key);
        }

        if (!root) return root;

        root->height = 1 + max(getHeight(root->left), getHeight(root->right));

        int balance = getBalance(root);

        if (balance > 1 && getBalance(root->left) >= 0)
            return rightRotate(root);

        if (balance < -1 && getBalance(root->right) <= 0)
            return leftRotate(root);

        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    void preOrder(AVLTreeNode* node) {
        if (node) {
            cout << node->key << " ";
            preOrder(node->left);
            preOrder(node->right);
        }
    }

    void inOrder(AVLTreeNode* node) {
        if (node) {
            inOrder(node->left);
            cout << node->key << " ";
            inOrder(node->right);
        }
    }

    void postOrder(AVLTreeNode* node) {
        if (node) {
            postOrder(node->left);
            postOrder(node->right);
            cout << node->key << " ";
        }
    }

    void clear(AVLTreeNode* node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

public:
    AVL() : root(nullptr) {}

    ~AVL() {
        clear(root);
    }

    void insert(int key) {
        root = insert(root, key);
    }

    void remove(int key) {
        root = remove(root, key);
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

bool isCommandValid(const string& command) {
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
    AVL avl;
    string input;
    getline(cin, input);
    stringstream ss(input);
    string command;

    while (ss >> command) {
        if (command == "PRE" || command == "IN" || command == "POST") {
            break;
        }

        if (!isCommandValid(command)) {
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
