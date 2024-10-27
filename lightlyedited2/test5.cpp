#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
using namespace std;

struct AVLTreeNode {
    int data;
    AVLTreeNode* left;
    AVLTreeNode* right;
    int height;

    AVLTreeNode(int value) : data(value), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
private:
    AVLTreeNode* root;

    int getHeight(AVLTreeNode* node) {
        return node ? node->height : 0;
    }

    int getBalance(AVLTreeNode* node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    AVLTreeNode* rotateRight(AVLTreeNode* y) {
        AVLTreeNode* x = y->left;
        AVLTreeNode* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

        return x;
    }

    AVLTreeNode* rotateLeft(AVLTreeNode* x) {
        AVLTreeNode* y = x->right;
        AVLTreeNode* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

        return y;
    }

    AVLTreeNode* insertNode(AVLTreeNode* node, int value) {
        if (!node) return new AVLTreeNode(value);

        if (value < node->data)
            node->left = insertNode(node->left, value);
        else if (value > node->data)
            node->right = insertNode(node->right, value);
        else
            return node;

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));

        int balance = getBalance(node);

        if (balance > 1 && value < node->left->data)
            return rotateRight(node);

        if (balance < -1 && value > node->right->data)
            return rotateLeft(node);

        if (balance > 1 && value > node->left->data) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if (balance < -1 && value < node->right->data) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    AVLTreeNode* minNode(AVLTreeNode* node) {
        AVLTreeNode* current = node;
        while (current->left != nullptr)
            current = current->left;
        return current;
    }

    AVLTreeNode* deleteNode(AVLTreeNode* root, int value) {
        if (!root) return root;

        if (value < root->data)
            root->left = deleteNode(root->left, value);
        else if (value > root->data)
            root->right = deleteNode(root->right, value);
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

            AVLTreeNode* temp = minNode(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }

        if (!root) return root;

        root->height = 1 + max(getHeight(root->left), getHeight(root->right));

        int balance = getBalance(root);

        if (balance > 1 && getBalance(root->left) >= 0)
            return rotateRight(root);

        if (balance < -1 && getBalance(root->right) <= 0)
            return rotateLeft(root);

        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }

        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }

        return root;
    }

    void preOrderTraversal(AVLTreeNode* node) {
        if (node) {
            cout << node->data << " ";
            preOrderTraversal(node->left);
            preOrderTraversal(node->right);
        }
    }

    void inOrderTraversal(AVLTreeNode* node) {
        if (node) {
            inOrderTraversal(node->left);
            cout << node->data << " ";
            inOrderTraversal(node->right);
        }
    }

    void postOrderTraversal(AVLTreeNode* node) {
        if (node) {
            postOrderTraversal(node->left);
            postOrderTraversal(node->right);
            cout << node->data << " ";
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
    AVLTree() : root(nullptr) {}

    ~AVLTree() {
        clear(root);
    }

    void insert(int value) {
        root = insertNode(root, value);
    }

    void remove(int value) {
        root = deleteNode(root, value);
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

bool isValidCommand(const string& command) {
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

    if (command == "PRE") {
        avl.preOrder();
    } else if (command == "IN") {
        avl.inOrder();
    } else if (command == "POST") {
        avl.postOrder();
    }

    return 0;
}
