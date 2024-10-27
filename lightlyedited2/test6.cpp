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

class AVL {
private:
    Node* root;

    int getHeight(Node* node) {
        return node ? node->height : 0;
    }

    int getBalance(Node* node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

        return x;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

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

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current->left != nullptr)
            current = current->left;
        return current;
    }

    Node* remove(Node* root, int key) {
        if (!root) return root;

        if (key < root->key)
            root->left = remove(root->left, key);
        else if (key > root->key)
            root->right = remove(root->right, key);
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

            Node* temp = minValueNode(root->right);
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

    void preOrder(Node* root) {
        if (root) {
            cout << root->key << " ";
            preOrder(root->left);
            preOrder(root->right);
        }
    }

    void inOrder(Node* root) {
        if (root) {
            inOrder(root->left);
            cout << root->key << " ";
            inOrder(root->right);
        }
    }

    void postOrder(Node* root) {
        if (root) {
            postOrder(root->left);
            postOrder(root->right);
            cout << root->key << " ";
        }
    }

    void clear(Node* node) {
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
    AVL avl;
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
