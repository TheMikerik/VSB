#include <iostream>

// Definition of a Node in a 2-3 Tree
struct Node {
    int key1;
    int key2;
    Node* left;
    Node* middle;
    Node* right;

    Node(int k1, int k2 = -1, Node* l = nullptr, Node* m = nullptr, Node* r = nullptr)
        : key1(k1), key2(k2), left(l), middle(m), right(r) {}
};

// Function to insert a key into a 2-3 Tree
Node* insert(Node* root, int key) {
    if (root == nullptr) {
        return new Node(key);
    }

    // If the node is a leaf node
    if (root->left == nullptr) {
        // Case 1: The node has only one key
        if (root->key2 == -1) {
            if (key < root->key1) {
                root->key2 = root->key1;
                root->key1 = key;
            } else {
                root->key2 = key;
            }
        }
        // Case 2: The node has two keys
        else {
            if (key < root->key1) {
                // Insert key to the left
                Node* newRoot = new Node(key);
                newRoot->left = new Node(key);
                newRoot->middle = root;
                return newRoot;
            } else if (key > root->key2) {
                // Insert key to the right
                Node* newRoot = new Node(key);
                newRoot->left = root;
                newRoot->middle = new Node(key);
                return newRoot;
            } else {
                // Insert key in the middle
                Node* newRoot = new Node(root->key1);
                newRoot->left = new Node(key);
                newRoot->middle = new Node(root->key2);
                return newRoot;
            }
        }
    }
    // Recursively insert into appropriate subtree
    if (key < root->key1) {
        root->left = insert(root->left, key);
    } else if (key > root->key2) {
        root->right = insert(root->right, key);
    } else {
        root->middle = insert(root->middle, key);
    }
    return root;
}

// Function to print the 2-3 Tree in-order
void inOrderTraversal(Node* root) {
    if (root) {
        inOrderTraversal(root->left);
        if (root->key2 == -1) {
            std::cout << root->key1 << " ";
        } else {
            std::cout << root->key1 << " " << root->key2 << " ";
        }
        inOrderTraversal(root->middle);
        inOrderTraversal(root->right);
    }
}

int main() {
    Node* root = nullptr;

    // Insert elements into the 2-3 Tree
    root = insert(root, 10);
    root = insert(root, 5);
    root = insert(root, 15);
    root = insert(root, 20);
    root = insert(root, 25);
    root = insert(root, 1);
    root = insert(root, 7);

    // Print the 2-3 Tree in-order
    inOrderTraversal(root);

    return 0;
}
