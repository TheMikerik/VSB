#include "BinaryBalanced.h"

BinaryBalanced::BinaryBalanced(){
        this->size = 0;
        this->Graph = nullptr;
}

BinaryBalanced::~BinaryBalanced(){
        delete this->Graph;
}

void BinaryBalanced::LoadGraph(const std::string& filename){
    short number;
    std::ifstream infile(filename);

    while(!infile.eof()) {
        infile >> number;
        this->Insert(number);
    }

    infile.close();
}

void BinaryBalanced::Insert(short inp){
    if(this->Graph == nullptr){
        this->size++;
        this->Graph = new Node(inp, this->size);
    }
    else {
        this->size++;
        this->GetPathFrom(this->size);
        // Navigate insertion into the next free position
        // Based on tracked path from function above
        Node *current = this->Graph;
        while (!path.empty()) {
            bool direction = path.top();
            path.pop();

            if (direction == LEFT) {
                if (current->left == nullptr) {
                    current->left = new Node(inp, size, current);
                } else {
                    current = current->left;
                }
            } else if (direction == RIGHT) {
                if (current->right == nullptr) {
                    current->right = new Node(inp, size, current);
                } else {
                    current = current->right;
                }
            }
        }
    }
}

void BinaryBalanced::GetPathFrom(short id_destination){
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

bool BinaryBalanced::CheckNearbyStatuses(Node *node) {
    if(node->parent != nullptr && node->parent->status == UNCHECKED){
        return true;
    }
    if(node->left != nullptr && node->left->status == UNCHECKED){
        return true;
    }
    if(node->right != nullptr && node->right->status == UNCHECKED){
        return true;
    }
    return false;
}

short BinaryBalanced::SendMessage(short start_id) {
    this->ResetStatuses();
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

    std::queue<Node*> q;
    current->status = CHECKED;
    q.push(current);
    short added = 1;
    short time = 0;

    std::vector<short> iter;
    iter.push_back(added);

    while(!q.empty()){
        added = 0;
        for(int i = 0; i < iter.at(time); i++) {
            current = q.front();
            q.pop();
            if (this->CheckNearbyStatuses(current)) {
                if (current->parent != nullptr && current->parent->status == UNCHECKED) {
                    current->parent->status = CHECKED;
                    q.push(current->parent);
                    added++;
                }
                if (current->left != nullptr && current->left->status == UNCHECKED) {
                    current->left->status = CHECKED;
                    q.push(current->left);
                    added++;
                }
                if (current->right != nullptr && current->right->status == UNCHECKED) {
                    current->right->status = CHECKED;
                    q.push(current->right);
                    added++;
                }
            }
        }
        iter.push_back(added);
        time++;
    }
    time--;
    return time;
}

void BinaryBalanced::SendMessagePrint(short start_id) {
    this->ResetStatuses();
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

    std::queue<Node*> q;
    current->status = CHECKED;
    q.push(current);
    short added = 1;
    short time = 1;

    std::vector<short> iter;
    iter.push_back(added);

    std::cout << "Starting from: " << current->value << std::endl;
    while(!q.empty()){
        bool iter_desc = true;
        added = 0;

        for(int i = 0; i < iter.at(time-1); i++) {
            current = q.front();
            q.pop();
            if (this->CheckNearbyStatuses(current)) {
                if (iter_desc){
                    std::cout << "Iteration " << time << ": ";
                    iter_desc = false;
                }
                if (current->parent != nullptr && current->parent->status == UNCHECKED) {
                    current->parent->status = CHECKED;
                    q.push(current->parent);
                    std::cout << current->parent->value << " ";
                    added++;
                }
                if (current->left != nullptr && current->left->status == UNCHECKED) {
                    current->left->status = CHECKED;
                    q.push(current->left);
                    std::cout << current->left->value << " ";
                    added++;
                }
                if (current->right != nullptr && current->right->status == UNCHECKED) {
                    current->right->status = CHECKED;
                    q.push(current->right);
                    std::cout << current->right->value << " ";
                    added++;
                }
            }
        }
        iter.push_back(added);
        std::cout << std::endl;
        time++;
    }
    std::cout << "Message handled trough entire graph" << "\n";
}

void BinaryBalanced::ResetStatuses(){
    Node* current = this->Graph;
    std::queue<Node*> q;
    q.push(current);

    while(!q.empty()){
        current = q.front();
        q.pop();
        current->status = UNCHECKED;
        if(current->left != nullptr){
            q.push(current->left);
        }
        if(current->right != nullptr) {
            q.push(current->right);
        }
    }
}

void BinaryBalanced::ShortestPath(){
    this->ResetStatuses();

    short min_time = -1;
    std::vector<short> min_id;

    for(short id = 1; id <= this->size; id++){
        short tmp = this->SendMessage(id);

        if(min_time == -1 || min_time <= tmp){
            min_time = tmp;
            min_id.push_back(id);
        }
    }

    std::cout << "\nShortest time: " << min_time << " iterations on those IDS: ";
    for(short id : min_id){
        std::cout << id << " ";
    }
    std::cout << std::endl;

    std::cout << "Shortest path example (" << "id:" << min_id.back()  << ")\n" << std::endl;
    this->SendMessagePrint(min_id.back());
    std::cout << "Checked " << this->size << " different routes\n\n";
}