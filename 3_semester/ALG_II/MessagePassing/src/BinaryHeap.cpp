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

    this->GetPathFrom(this->size);

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

short BinaryHeap::SearchNodeID(short inp){
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

void BinaryHeap::GetPathFrom(short id_destination){
    while(id_destination != 1){
        if(id_destination % 2 == 1){
            path.push(RIGHT);
            id_destination -= 1;
        }
        else{
            path.push(LEFT);
        }

        id_destination /= 2;
    }
}

bool BinaryHeap::CheckNearbyStatuses(Node *node) {
    if(node->parent != nullptr){
        node->parent->status = UNCHECKED;
        return true;
    }
    if(node->left != nullptr){
        node->left->status = UNCHECKED;
        return true;
    }
    if(node->right != nullptr){
        node->right->status = UNCHECKED;
        return true;
    }
    return false;
}

void BinaryHeap::SendMessage(short start_number) {
    short start_id = this->SearchNodeID(start_number);
    this->GetPathFrom(start_id);

    Node *current = this->Graph;
    while(!path.empty()){
        bool direction = path.top();
        path.pop();

        if(direction == LEFT){
            current = current->left;
        }
        else if(direction == RIGHT){
            current = current->right;
        }
    }

    std::cout << "Seeked node was found " << current->value << " and ID " << current->ID << std::endl;
    std::queue<Node*> q;
    current->status = CHECKED;
    q.push(current);

    short iter = 0;

    while(!q.empty()){

        current = q.front();
        q.pop();

        if(this->CheckNearbyStatuses(current)){
            std::cout << "Iteration " << iter << ": ";

            if (current->parent != nullptr && current->parent->status == UNCHECKED) {
                current->parent->status = CHECKED;
                q.push(current->parent);
                std::cout << current->parent->value << " (ID_" << current->parent->ID << ") ";
            }
            if (current->left != nullptr && current->left->status == UNCHECKED) {
                current->left->status = CHECKED;
                q.push(current->left);
                std::cout << current->left->value << " (ID_" << current->left->ID << ") ";
            }
            if (current->right != nullptr && current->right->status == UNCHECKED) {
                current->right->status = CHECKED;
                q.push(current->right);
                std::cout << current->right->value << " (ID_" << current->right->ID << ") ";
            }
            std::cout << std::endl;
            iter++;
        }
    }
}