#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
using namespace std;

class TreeNode {
public:
    int value;
    TreeNode* leftChild;
    TreeNode* rightChild;
    int height;

    TreeNode(int val) : value(val), leftChild(nullptr), rightChild(nullptr), height(1) {}
};

class AVL {
private:
    TreeNode* rootNode;

    int getNodeHeight(TreeNode* node) {
        return node ? node->height : 0;
    }

    int balanceFactor(TreeNode* node) {
        return node ? getNodeHeight(node->leftChild) - getNodeHeight(node->rightChild) : 0;
    }

    TreeNode* rightRotate(TreeNode* y) {
        TreeNode* x = y->leftChild;
        TreeNode* T2 = x->rightChild;

        x->rightChild = y;
        y->leftChild = T2;

        y->height = max(getNodeHeight(y->leftChild), getNodeHeight(y->rightChild)) + 1;
        x->height = max(getNodeHeight(x->leftChild), getNodeHeight(x->rightChild)) + 1;

        return x;
    }

    TreeNode* leftRotate(TreeNode* x) {
        TreeNode* y = x->rightChild;
        TreeNode* T2 = y->leftChild;

        y->leftChild = x;
        x->rightChild = T2;

        x->height = max(getNodeHeight(x->leftChild), getNodeHeight(x->rightChild)) + 1;
        y->height = max(getNodeHeight(y->leftChild), getNodeHeight(y->rightChild)) + 1;

        return y;
    }

    TreeNode* insertNode(TreeNode* node, int key) {
        if (!node)
            return new TreeNode(key);

        if (key < node->value)
            node->leftChild = insertNode(node->leftChild, key);
        else if (key > node->value)
            node->rightChild = insertNode(node->rightChild, key);
        else
            return node;

        node->height = 1 + max(getNodeHeight(node->leftChild), getNodeHeight(node->rightChild));

        int balance = balanceFactor(node);

        if (balance > 1 && key < node->leftChild->value)
            return rightRotate(node);

        if (balance < -1 && key > node->rightChild->value)
            return leftRotate(node);

        if (balance > 1 && key > node->leftChild->value) {
            node->leftChild = leftRotate(node->leftChild);
            return rightRotate(node);
        }

        if (balance < -1 && key < node->rightChild->value) {
            node->rightChild = rightRotate(node->rightChild);
            return leftRotate(node);
        }

        return node;
    }

    TreeNode* findMinNode(TreeNode* node) {
        TreeNode* current = node;
        while (current && current->leftChild != nullptr)
            current = current->leftChild;
        return current;
    }

    TreeNode* removeNode(TreeNode* root, int key) {
        if (!root)
            return root;

        if (key < root->value)
            root->leftChild = removeNode(root->leftChild, key);
        else if (key > root->value)
            root->rightChild = removeNode(root->rightChild, key);
        else {
            if (!root->leftChild) {
                TreeNode* temp = root->rightChild;
                delete root;
                return temp;
            } else if (!root->rightChild) {
                TreeNode* temp = root->leftChild;
                delete root;
                return temp;
            }

            TreeNode* temp = findMinNode(root->rightChild);
            root->value = temp->value;
            root->rightChild = removeNode(root->rightChild, temp->value);
        }

        if (!root)
            return root;

        root->height = 1 + max(getNodeHeight(root->leftChild), getNodeHeight(root->rightChild));

        int balance = balanceFactor(root);

        if (balance > 1 && balanceFactor(root->leftChild) >= 0)
            return rightRotate(root);

        if (balance > 1 && balanceFactor(root->leftChild) < 0) {
            root->leftChild = leftRotate(root->leftChild);
            return rightRotate(root);
        }

        if (balance < -1 && balanceFactor(root->rightChild) <= 0)
            return leftRotate(root);

        if (balance < -1 && balanceFactor(root->rightChild) > 0) {
            root->rightChild = rightRotate(root->rightChild);
            return leftRotate(root);
        }

        return root;
    }

    void preOrderTraversal(TreeNode* root) {
        if (!root)
            return;
        cout << root->value << " ";
        preOrderTraversal(root->leftChild);
        preOrderTraversal(root->rightChild);
    }

    void inOrderTraversal(TreeNode* root) {
        if (!root)
            return;
        inOrderTraversal(root->leftChild);
        cout << root->value << " ";
        inOrderTraversal(root->rightChild);
    }

    void postOrderTraversal(TreeNode* root) {
        if (!root)
            return;
        postOrderTraversal(root->leftChild);
        postOrderTraversal(root->rightChild);
        cout << root->value << " ";
    }

    void clearTree(TreeNode* node) {
        if (!node) return;
        clearTree(node->leftChild);
        clearTree(node->rightChild);
        delete node;
    }

public:
    AVL() : rootNode(nullptr) {}

    ~AVL() {
        clearTree(rootNode);
    }

    void add(int key) {
        rootNode = insertNode(rootNode, key);
    }

    void remove(int key) {
        rootNode = removeNode(rootNode, key);
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

bool validateCommand(const string& cmd) {
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
    AVL tree;
    string input, cmd;
    getline(cin, input);
    stringstream ss(input);
    string finishCommand;

    while (ss >> cmd) {
        if (cmd == "PRE" || cmd == "IN" || cmd == "POST") {
            finishCommand = cmd;
            break;
        }

        if (!validateCommand(cmd)) {
            cerr << "Invalid command: " << cmd << endl;
            continue;
        }

        if (cmd[0] == 'A') {
            tree.add(stoi(cmd.substr(1)));
        } else if (cmd[0] == 'D') {
            tree.remove(stoi(cmd.substr(1)));
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
