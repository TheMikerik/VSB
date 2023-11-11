#include "BinaryHeap.h"

BinaryHeap::BinaryHeap(short inp){
        this->size = 1;
        this->Graph = new Node(inp, size);
}

BinaryHeap::~BinaryHeap(){
        delete this->Graph;
}

void BinaryHeap::Insert(short inp){
    this->size++;
    int tmp_position = this->size;

    // Scans path to next free position
    // LEFT = even number; RIGHT = odd number
    while(tmp_position != 1){
        if(tmp_position % 2 == 1){
            path.push(RIGHT);
            tmp_position -= 1;
        }
        else{
            path.push(LEFT);
        }

        tmp_position /= 2;
    }

    // Navigate insertion into the next free position
    // Based on tracked path from function above
    Node *current = this->Graph;
    while(!path.empty()){
        bool direction = path.top();
        path.pop();

        if(direction == LEFT){
            if(current->left == nullptr){
                current->left = new Node(inp, size, current);
            }
            else {
                current = current->left;
            }
        }
        else if(direction == RIGHT){
            if(current->right == nullptr){
                current->right = new Node(inp, size, current);
            }
            else{
                current = current->right;
            }
        }
    }
}

short BinaryHeap::SearchNode(short inp){
    std::queue<Node*> q;
    Node* current = this->Graph;
    q.push(current);

    while(!q.empty()){
        current = q.front();
        q.pop();

        if(current->value == inp){
            return current->ID;
        }

        if(current->left != nullptr){
            q.push(current->left);
        }
        if(current->right!= nullptr){
            q.push(current->right);
        }
    }
    throw std::runtime_error("Number was not found");
}

void BinaryHeap::SendMessage(short start_number) {
}