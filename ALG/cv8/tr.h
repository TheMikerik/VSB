#include <iostream>
using namespace std;

class Tree2{
    public:
        string key; string value; Tree2* next_l; Tree2* next_r;

        Tree2(string c_key, string c_value){
            this->key = c_key;
            this->value = c_value;
            this->next_l = NULL;
            this->next_r = NULL;
        }        
};

void CreateChild(Tree2* parent, int depth, int max_depth){
    if (depth == max_depth){ return;}

    Tree2* left_child = new Tree2(parent->key + "l.", parent->value + "l.");
    parent->next_l = left_child;
    CreateChild(left_child, depth + 1, max_depth);

    Tree2* right_child = new Tree2(parent->key + "r.", parent->value + "r.");
    parent->next_r = right_child;
    CreateChild(right_child, depth + 1, max_depth);
}

void PrintTree(Tree2* parent){
    if (parent == NULL) {return;}

    cout << parent->key << " + " << parent->value << endl;

    PrintTree(parent->next_l);
    PrintTree(parent->next_r);
}

void CreateTree(Tree2* start){
    int max_depth;
    cout << "Input depth of the binary tree: ";
    cin >> max_depth;
    cout << "You created " << max_depth << " values deep binary tree." << endl;

    CreateChild(start, 0, max_depth);
}

void PrintBinaryTree(Tree2* start){
    char y_or_no;
    cout << "Tree has been created. Do you want to print it out?    y/n" << endl;
    cin >> y_or_no;

    if (y_or_no == 'y'){
        PrintTree(start);
    }
    else {
        cout << "Okay, so lets move to the next exercise." << endl;
    }
}