#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

// https://www.programiz.com/dsa/avl-tree

using namespace std;

struct Node{
    int value;
    Node* parent;
    Node* left;
    Node* right;

    Node(int val){
        this->value = val;
    }
};

Node* LeftRotate(Node* tree){       //  tree.left.left || tree.left.right
    if(tree->parent = nullptr){
        tree->parent = tree;
    }
    else if(tree->parent){
        Node* tmp = tree;
    }
}

Node* InsertValue(Node* tree, int val){
    if(tree == nullptr){
        
        // Tady rotace

        return new Node(val);
    }

    if(val < tree->value){
        tree->left = InsertValue(tree->left, val);
    }
    else if(val > tree->value){
        tree->right = InsertValue(tree->right, val);
    }

    
    return tree;
}

Node* generate_AVL(vector<int> input){
    Node* tree = nullptr;

    while( !input.empty() ){
        int tmp = input.back();
        input.pop_back();

        tree = InsertValue(tree, tmp);
    }
    return tree;
}

void inorder(Node* node){
    if (!node) return; 
    inorder(node->left);
    cout << node->value << " ";
    inorder(node->right);
}

int main(){
    vector<int> avlVector = {20, 10, 5, 13, 18, 25, 26, 27, 28, 12};
    Node* AVLtree;

    AVLtree = generate_AVL(avlVector);
    inorder(AVLtree);
    cout << endl;
    return 0;
}