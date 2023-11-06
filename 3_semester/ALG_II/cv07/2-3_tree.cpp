#include <iostream>
#include <vector>
#include "Node.cpp"

class TwoThreeTree {
private:
    Node* root;

    void splitNode(Node* parent, int index) {
        Node* leftChild = parent->children[index];
        Node* rightChild = new Node();

        rightChild->isLeaf = leftChild->isLeaf;
        rightChild->keyCount = 1;

        rightChild->keys[0] = leftChild->keys[2];

        if (!leftChild->isLeaf) {
            rightChild->children[1] = leftChild->children[2];
            rightChild->children[2] = leftChild->children[3];
        }

        leftChild->keyCount = 1;

        parent->children[index] = leftChild;
        parent->children[index + 1] = rightChild;

        for (int i = parent->keyCount; i > index; --i) {
            parent->keys[i] = parent->keys[i - 1];
        }

        parent->keys[index] = leftChild->keys[1];
        parent->keyCount++;
    }

    void insertNonFull(Node* node, int value) {
        int i = node->keyCount;

        if (node->isLeaf) {
            while (i > 0 && value < node->keys[i - 1]) {
                node->keys[i] = node->keys[i - 1];
                i--;
            }

            node->keys[i] = value;
            node->keyCount++;
        }
        else {
            while (i > 0 && value < node->keys[i - 1]) {
                i--;
            }

            if (node->children[i]->keyCount == 3) {
                splitNode(node, i);

                if (value > node->keys[i]) {
                    i++;
                }
            }

            insertNonFull(node->children[i], value);
        }
    }

    void printInOrder(Node* node) {
        if (node == nullptr) {
            return;
        }

        if (!node->isLeaf) {
            printInOrder(node->children[0]);
        }

        for (int i = 0; i < node->keyCount; ++i) {
            cout << node->keys[i] << " ";
            if (!node->isLeaf) {
                printInOrder(node->children[i + 1]);
            }
        }
    }

    void deleteValue(Node* node, int value) {
        int i = 0;
        while (i < node->keyCount && value > node->keys[i]) {
            i++;
        }

        if (node->isLeaf) {
            if (i < node->keyCount && value == node->keys[i]) {
                for (int j = i; j < node->keyCount - 1; j++) {
                    node->keys[j] = node->keys[j + 1];
                }
                node->keyCount--;
            }
        }
        else {
            if (i < node->keyCount && value == node->keys[i]) {
                Node* maxLeft = node->children[i];
                while (!maxLeft->isLeaf) {
                    maxLeft = maxLeft->children[maxLeft->keyCount];
                }
                int maxLeftValue = maxLeft->keys[maxLeft->keyCount - 1];
                node->keys[i] = maxLeftValue;
                deleteValue(maxLeft, maxLeftValue);
            }
            else {
                deleteValue(node->children[i], value);
            }
        }
    }

    bool searchValue(Node* node, int value) {
        int i = 0;
        while (i < node->keyCount && value > node->keys[i]) {
            i++;
        }

        if (i < node->keyCount && value == node->keys[i]) {
            return true;
        }

        if (node->isLeaf) {
            return false;
        }

        return searchValue(node->children[i], value);
    }


public:
    TwoThreeTree() : root(nullptr) {}

    void insert(int value) {
        if (root == nullptr) {
            root = new Node();
            root->keys[0] = value;
            root->keyCount = 1;
        }
        else {
            if (root->keyCount == 3) {
                Node* newRoot = new Node();
                newRoot->isLeaf = false;
                newRoot->children[0] = root;

                splitNode(newRoot, 0);

                int i = (value < newRoot->keys[0]) ? 0 : 1;
                insertNonFull(newRoot->children[i], value);

                root = newRoot;
            }
            else {
                insertNonFull(root, value);
            }
        }
    }

    void deleteValue(int value) {
        if (root) {
            deleteValue(root, value);
            if (root->keyCount == 0) {
                Node* newRoot = root->children[0];
                delete root;
                root = newRoot;
            }
        }
    }

    bool searchValue(int value) {
        if (root) {
            return searchValue(root, value);
        }
        return false;
    }

    ~TwoThreeTree() {
        delete root;
    }
    void printInOrder() {
        printInOrder(root);
        cout << endl;
    }
};