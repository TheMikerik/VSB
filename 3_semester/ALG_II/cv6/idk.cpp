#include <iostream>
#include <vector>
using namespace std;

class TwoThreeTree {
private:
    struct Node {
        vector<int> keys;
        vector<Node*> children;
        Node* parent;

        Node(int key) {
            keys.push_back(key);
            parent = nullptr;
        }
    };

    Node* root;

    void splitNode(Node* node);
    void insert(Node* node, int key);

public:
    TwoThreeTree() : root(nullptr) {}

    void insert(int key);
    void printAscending();

    // Implement other methods like deletion, searching, etc.
};

void TwoThreeTree::splitNode(Node* node) {
    if (node->keys.size() == 3) {
        if (node == root) {
            root = new Node(node->keys[1]);
            Node* leftChild = new Node(node->keys[0]);
            Node* rightChild = new Node(node->keys[2]);
            root->children.push_back(leftChild);
            root->children.push_back(rightChild);
            leftChild->parent = root;
            rightChild->parent = root;
            splitNode(leftChild);
            splitNode(rightChild);
        } else {
            Node* parent = node->parent;
            int index = 0;
            while (index < parent->keys.size() && parent->keys[index] < node->keys[1]) {
                index++;
            }
            parent->keys.insert(parent->keys.begin() + index, node->keys[1]);
            parent->children.erase(parent->children.begin() + index);
            Node* leftChild = new Node(node->keys[0]);
            Node* rightChild = new Node(node->keys[2]);
            parent->children.insert(parent->children.begin() + index, leftChild);
            parent->children.insert(parent->children.begin() + index + 1, rightChild);
            leftChild->parent = parent;
            rightChild->parent = parent;
            splitNode(parent);
        }
    }
}

void TwoThreeTree::insert(int key) {
    if (root == nullptr) {
        root = new Node(key);
    } else {
        insert(root, key);
    }
}

void TwoThreeTree::insert(Node* node, int key) {
    if (node->children.empty()) {
        node->keys.push_back(key);
        sort(node->keys.begin(), node->keys.end());
        splitNode(node);
    } else {
        int index = 0;
        while (index < node->keys.size() && key > node->keys[index]) {
            index++;
        }
        insert(node->children[index], key);
    }
}

void TwoThreeTree::printAscending() {
    if (root) {
        vector<int> result;
        printAscending(root, result);

        for (int key : result) {
            cout << key << " ";
        }
        cout << endl;
    }
}

void TwoThreeTree::printAscending(Node* node, vector<int>& result) {
    if (node) {
        if (node->children.size() == 0) {
            for (int key : node->keys) {
                result.push_back(key);
            }
        } else {
            for (int i = 0; i < node->keys.size(); ++i) {
                printAscending(node->children[i], result);
                result.push_back(node->keys[i]);
            }
            printAscending(node->children[node->keys.size()], result);
        }
    }
}


int main() {
    TwoThreeTree tree;

    // Insert elements into the tree
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(7);
    tree.insert(12);
    tree.insert(20);

    // Print elements in ascending order
    tree.printAscending();

    return 0;
}
