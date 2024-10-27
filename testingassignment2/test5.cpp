#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
using namespace std;

class TreeNode {
public:
    int value;
    TreeNode* leftBranch;
    TreeNode* rightBranch;
    int heightVal;

    TreeNode(int val) : value(val), leftBranch(nullptr), rightBranch(nullptr), heightVal(1) {}
};

class AVLTreeController {
private:
    TreeNode* root;

    int getNodeHeight(TreeNode* node) {
        return node ? node->heightVal : 0;
    }

    int calculateBalance(TreeNode* node) {
        return node ? getNodeHeight(node->leftBranch) - getNodeHeight(node->rightBranch) : 0;
    }

    TreeNode* rotateRight(TreeNode* y) {
        TreeNode* x = y->leftBranch;
        TreeNode* T2 = x->rightBranch;

        x->rightBranch = y;
        y->leftBranch = T2;

        y->heightVal = max(getNodeHeight(y->leftBranch), getNodeHeight(y->rightBranch)) + 1;
        x->heightVal = max(getNodeHeight(x->leftBranch), getNodeHeight(x->rightBranch)) + 1;

        return x;
    }

    TreeNode* rotateLeft(TreeNode* x) {
        TreeNode* y = x->rightBranch;
        TreeNode* T2 = y->leftBranch;

        y->leftBranch = x;
        x->rightBranch = T2;

        x->heightVal = max(getNodeHeight(x->leftBranch), getNodeHeight(x->rightBranch)) + 1;
        y->heightVal = max(getNodeHeight(y->leftBranch), getNodeHeight(y->rightBranch)) + 1;

        return y;
    }

    TreeNode* insertNode(TreeNode* node, int value) {
        if (!node) return new TreeNode(value);

        if (value < node->value)
            node->leftBranch = insertNode(node->leftBranch, value);
        else if (value > node->value)
            node->rightBranch = insertNode(node->rightBranch, value);
        else
            return node;

        node->heightVal = 1 + max(getNodeHeight(node->leftBranch), getNodeHeight(node->rightBranch));

        int balance = calculateBalance(node);

        if (balance > 1 && value < node->leftBranch->value) return rotateRight(node);
        if (balance < -1 && value > node->rightBranch->value) return rotateLeft(node);
        if (balance > 1 && value > node->leftBranch->value) {
            node->leftBranch = rotateLeft(node->leftBranch);
            return rotateRight(node);
        }
        if (balance < -1 && value < node->rightBranch->value) {
            node->rightBranch = rotateRight(node->rightBranch);
            return rotateLeft(node);
        }

        return node;
    }

    TreeNode* getMinNode(TreeNode* node) {
        while (node->leftBranch) node = node->leftBranch;
        return node;
    }

    TreeNode* deleteNode(TreeNode* root, int value) {
        if (!root) return root;

        if (value < root->value) {
            root->leftBranch = deleteNode(root->leftBranch, value);
        } else if (value > root->value) {
            root->rightBranch = deleteNode(root->rightBranch, value);
        } else {
            if (!root->leftBranch || !root->rightBranch) {
                TreeNode* temp = root->leftBranch ? root->leftBranch : root->rightBranch;
                delete root;
                return temp;
            }

            TreeNode* temp = getMinNode(root->rightBranch);
            root->value = temp->value;
            root->rightBranch = deleteNode(root->rightBranch, temp->value);
        }

        if (!root) return root;

        root->heightVal = 1 + max(getNodeHeight(root->leftBranch), getNodeHeight(root->rightBranch));
        int balance = calculateBalance(root);

        if (balance > 1 && calculateBalance(root->leftBranch) >= 0) return rotateRight(root);
        if (balance > 1 && calculateBalance(root->leftBranch) < 0) {
            root->leftBranch = rotateLeft(root->leftBranch);
            return rotateRight(root);
        }
        if (balance < -1 && calculateBalance(root->rightBranch) <= 0) return rotateLeft(root);
        if (balance < -1 && calculateBalance(root->rightBranch) > 0) {
            root->rightBranch = rotateRight(root->rightBranch);
            return rotateLeft(root);
        }

        return root;
    }

    void printInOrder(TreeNode* node) {
        if (node) {
            printInOrder(node->leftBranch);
            cout << node->value << " ";
            printInOrder(node->rightBranch);
        }
    }

    void printPreOrder(TreeNode* node) {
        if (node) {
            cout << node->value << " ";
            printPreOrder(node->leftBranch);
            printPreOrder(node->rightBranch);
        }
    }

    void printPostOrder(TreeNode* node) {
        if (node) {
            printPostOrder(node->leftBranch);
            printPostOrder(node->rightBranch);
            cout << node->value << " ";
        }
    }

public:
    AVLTreeController() : root(nullptr) {}

    void addValue(int value) {
        root = insertNode(root, value);
    }

    void removeValue(int value) {
        root = deleteNode(root, value);
    }

    void traverseTree(const string& order) {
        if (order == "IN")
            printInOrder(root);
        else if (order == "PRE")
            printPreOrder(root);
        else if (order == "POST")
            printPostOrder(root);
        cout << endl;
    }
};

bool validateCommand(const string& command) {
    if (command.empty()) return false;

    if (command[0] == 'A' || command[0] == 'D') {
        return command.size() > 1 && all_of(command.begin() + 1, command.end(), ::isdigit);
    }
    return command == "IN" || command == "PRE" || command == "POST";
}

int main() {
    AVLTreeController avlController;
    string input;
    getline(cin, input);
    stringstream ss(input);
    string command;

    while (ss >> command) {
        if (command == "IN" || command == "PRE" || command == "POST") {
            avlController.traverseTree(command);
            break;
        }

        if (!validateCommand(command)) {
            cerr << "Invalid command: " << command << endl;
            continue;
        }

        if (command[0] == 'A') avlController.addValue(stoi(command.substr(1)));
        else if (command[0] == 'D') avlController.removeValue(stoi(command.substr(1)));
    }
    return 0;
}
