#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
using namespace std;

class TreeNode {
public:
    int value;
    TreeNode* leftNode;
    TreeNode* rightNode;
    int nodeHeight;

    TreeNode(int val) : value(val), leftNode(nullptr), rightNode(nullptr), nodeHeight(1) {}
};

class AVL {
private:
    TreeNode* rootNode;

    int getHeight(TreeNode* node) {
        return node ? node->nodeHeight : 0;
    }

    int getBalance(TreeNode* node) {
        return node ? getHeight(node->leftNode) - getHeight(node->rightNode) : 0;
    }

    TreeNode* rotateToRight(TreeNode* y) {
        TreeNode* x = y->leftNode;
        TreeNode* temp = x->rightNode;

        x->rightNode = y;
        y->leftNode = temp;

        y->nodeHeight = max(getHeight(y->leftNode), getHeight(y->rightNode)) + 1;
        x->nodeHeight = max(getHeight(x->leftNode), getHeight(x->rightNode)) + 1;

        return x;
    }

    TreeNode* rotateToLeft(TreeNode* x) {
        TreeNode* y = x->rightNode;
        TreeNode* temp = y->leftNode;

        y->leftNode = x;
        x->rightNode = temp;

        x->nodeHeight = max(getHeight(x->leftNode), getHeight(x->rightNode)) + 1;
        y->nodeHeight = max(getHeight(y->leftNode), getHeight(y->rightNode)) + 1;

        return y;
    }

    TreeNode* insertNode(TreeNode* node, int value) {
        if (!node)
            return new TreeNode(value);

        if (value < node->value)
            node->leftNode = insertNode(node->leftNode, value);
        else if (value > node->value)
            node->rightNode = insertNode(node->rightNode, value);
        else
            return node;

        node->nodeHeight = 1 + max(getHeight(node->leftNode), getHeight(node->rightNode));

        int balance = getBalance(node);

        if (balance > 1) {
            if (value < node->leftNode->value)
                return rotateToRight(node);
            node->leftNode = rotateToLeft(node->leftNode);
            return rotateToRight(node);
        }

        if (balance < -1) {
            if (value > node->rightNode->value)
                return rotateToLeft(node);
            node->rightNode = rotateToRight(node->rightNode);
            return rotateToLeft(node);
        }

        return node;
    }

    TreeNode* getMinValue(TreeNode* node) {
        TreeNode* current = node;
        while (current->leftNode != nullptr)
            current = current->leftNode;
        return current;
    }

    TreeNode* removeNode(TreeNode* root, int value) {
        if (!root)
            return root;

        if (value < root->value)
            root->leftNode = removeNode(root->leftNode, value);
        else if (value > root->value)
            root->rightNode = removeNode(root->rightNode, value);
        else {
            if (!root->leftNode || !root->rightNode) {
                TreeNode* temp = root->leftNode ? root->leftNode : root->rightNode;
                delete root;
                return temp;
            }

            TreeNode* temp = getMinValue(root->rightNode);
            root->value = temp->value;
            root->rightNode = removeNode(root->rightNode, temp->value);
        }

        if (!root)
            return root;

        root->nodeHeight = 1 + max(getHeight(root->leftNode), getHeight(root->rightNode));

        int balance = getBalance(root);

        if (balance > 1 && getBalance(root->leftNode) >= 0)
            return rotateToRight(root);
        if (balance > 1 && getBalance(root->leftNode) < 0) {
            root->leftNode = rotateToLeft(root->leftNode);
            return rotateToRight(root);
        }

        if (balance < -1 && getBalance(root->rightNode) <= 0)
            return rotateToLeft(root);
        if (balance < -1 && getBalance(root->rightNode) > 0) {
            root->rightNode = rotateToRight(root->rightNode);
            return rotateToLeft(root);
        }

        return root;
    }

    void preOrder(TreeNode* root) {
        if (root) {
            cout << root->value << " ";
            preOrder(root->leftNode);
            preOrder(root->rightNode);
        }
    }

    void inOrder(TreeNode* root) {
        if (root) {
            inOrder(root->leftNode);
            cout << root->value << " ";
            inOrder(root->rightNode);
        }
    }

    void postOrder(TreeNode* root) {
        if (root) {
            postOrder(root->leftNode);
            postOrder(root->rightNode);
            cout << root->value << " ";
        }
    }

    void destroyTree(TreeNode* node) {
        if (node) {
            destroyTree(node->leftNode);
            destroyTree(node->rightNode);
            delete node;
        }
    }

public:
    AVL() : rootNode(nullptr) {}

    ~AVL() {
        destroyTree(rootNode);
    }

    void insert(int value) {
        rootNode = insertNode(rootNode, value);
    }

    void remove(int value) {
        rootNode = removeNode(rootNode, value);
    }

    void displayPreOrder() {
        if (!rootNode) {
            cout << "No elements" << endl;
        } else {
            preOrder(rootNode);
            cout << endl;
        }
    }

    void displayInOrder() {
        if (!rootNode) {
            cout << "No elements" << endl;
        } else {
            inOrder(rootNode);
            cout << endl;
        }
    }

    void displayPostOrder() {
        if (!rootNode) {
            cout << "No elements" << endl;
        } else {
            postOrder(rootNode);
            cout << endl;
        }
    }
};

bool isCmdValid(const string& command) {
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
    AVL tree;
    string input, cmd;
    getline(cin, input);
    stringstream ss(input);
    string commandEnd;

    while (ss >> cmd) {
        if (cmd == "PRE" || cmd == "IN" || cmd == "POST") {
            commandEnd = cmd;
            break;
        }

        if (!isCmdValid(cmd)) {
            cerr << "Invalid input: " << cmd << endl;
            continue;
        }

        if (cmd[0] == 'A') {
            tree.insert(stoi(cmd.substr(1)));
        } else if (cmd[0] == 'D') {
            tree.remove(stoi(cmd.substr(1)));
        }
    }

    if (commandEnd == "PRE") {
        tree.displayPreOrder();
    } else if (commandEnd == "IN") {
        tree.displayInOrder();
    } else if (commandEnd == "POST") {
        tree.displayPostOrder();
    }

    return 0;
}
