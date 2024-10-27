#include <iostream>
#include <stack>
#include <algorithm>
#include <sstream>
#include <string>
using namespace std;

class Node {
public:
    int key;
    Node* left;
    Node* right;
    int height;
    Node(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
private:
    Node* root;

    int nodeHeight(Node* node) {
        return node ? node->height : 0;
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

    void updateHeight(Node* node) {
        node->height = max(nodeHeight(node->left), nodeHeight(node->right)) + 1;
    }

    Node* balance(Node* node) {
        int balanceFactor = nodeHeight(node->left) - nodeHeight(node->right);
        if (balanceFactor > 1) {
            if (nodeHeight(node->left->left) >= nodeHeight(node->left->right)) {
                return rotateRight(node);
            } else {
                node->left = rotateLeft(node->left);
                return rotateRight(node);
            }
        } else if (balanceFactor < -1) {
            if (nodeHeight(node->right->right) >= nodeHeight(node->right->left)) {
                return rotateLeft(node);
            } else {
                node->right = rotateRight(node->right);
                return rotateLeft(node);
            }
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
                Node* minLargerNode = findMinNode(node->right);
                node->key = minLargerNode->key;
                node->right = deleteHelper(node->right, minLargerNode->key);
            }
        }
        updateHeight(node);
        return balance(node);
    }

    Node* findMinNode(Node* node) {
        Node* current = node;
        while (current && current->left) current = current->left;
        return current;
    }

    void inOrderIterative(Node* node) {
        stack<Node*> nodeStack;
        Node* current = node;
        while (current || !nodeStack.empty()) {
            while (current) {
                nodeStack.push(current);
                current = current->left;
            }
            current = nodeStack.top();
            nodeStack.pop();
            cout << current->key << " ";
            current = current->right;
        }
    }

    void preOrderIterative(Node* node) {
        if (!node) return;
        stack<Node*> nodeStack;
        nodeStack.push(node);
        while (!nodeStack.empty()) {
            Node* current = nodeStack.top();
            nodeStack.pop();
            cout << current->key << " ";
            if (current->right) nodeStack.push(current->right);
            if (current->left) nodeStack.push(current->left);
        }
    }

    void postOrderIterative(Node* node) {
        stack<Node*> s1, s2;
        s1.push(node);
        while (!s1.empty()) {
            Node* current = s1.top();
            s1.pop();
            s2.push(current);
            if (current->left) s1.push(current->left);
            if (current->right) s1.push(current->right);
        }
        while (!s2.empty()) {
            cout << s2.top()->key << " ";
            s2.pop();
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

    void traverse(const string& order) {
        if (order == "IN") {
            inOrderIterative(root);
        } else if (order == "PRE") {
            preOrderIterative(root);
        } else if (order == "POST") {
            postOrderIterative(root);
        }
        cout << endl;
    }
};

bool isValidCommand(const string& command) {
    if (command.empty()) return false;
    if (command[0] == 'A' || command[0] == 'D') {
        return command.size() > 1 && all_of(command.begin() + 1, command.end(), ::isdigit);
    }
    return command == "IN" || command == "PRE" || command == "POST";
}

int main() {
    AVLTree avl;
    string input;
    getline(cin, input);
    stringstream ss(input);
    string command;

    while (ss >> command) {
        if (command == "IN" || command == "PRE" || command == "POST") {
            avl.traverse(command);
            break;
        }
        if (!isValidCommand(command)) {
            cerr << "Invalid command: " << command << endl;
            continue;
        }
        if (command[0] == 'A') avl.insert(stoi(command.substr(1)));
        else if (command[0] == 'D') avl.remove(stoi(command.substr(1)));
    }
    return 0;
}
