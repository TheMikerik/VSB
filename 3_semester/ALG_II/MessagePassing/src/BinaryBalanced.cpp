#include "BinaryBalanced.h"

BinaryBalanced::BinaryBalanced(){
        this->size = 0;
        this->Graph = nullptr;
}

BinaryBalanced::~BinaryBalanced(){
    if (this->Graph != nullptr) {
        this->DeleteGraph(this->Graph);
        this->Graph = nullptr;
    }
}

void BinaryBalanced::DeleteGraph(Node* node) {
    if (node != nullptr) {
        this->DeleteGraph(node->left);
        this->DeleteGraph(node->right);
        delete node;
    }
}

void BinaryBalanced::LoadGraph(const std::string& filename){
    short number;
    std::ifstream infile(filename);

    if (!infile.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return;
    }
    else {
        while (!infile.eof()) {
            infile >> number;
            this->Insert(number);
        }
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

short BinaryBalanced::SendMessage(short start_id, bool print) {
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
    short from_q = 1;
    short iterations = 0;

    std::vector<short> added;
    added.push_back(from_q);

    if(print){ std::cout << "\tStarting from: " << current->ID << std::endl;}

    while(!q.empty()){
        iterations++;
        bool iter_desc = print;
        from_q = 0;

        for(int i = 0; i < added.at(iterations - 1); i++) {
            current = q.front();
            q.pop();
            if (this->CheckNearbyStatuses(current)) {
                if (iter_desc){
                    std::cout << "\tIteration " << iterations << ": ";
                    iter_desc = false;
                }
                if (current->parent != nullptr && current->parent->status == UNCHECKED) {
                    current->parent->status = CHECKED;
                    q.push(current->parent);
                    if(print){ std::cout << current->parent->ID << " "; }
                    from_q++;
                }
                if (current->left != nullptr && current->left->status == UNCHECKED) {
                    current->left->status = CHECKED;
                    q.push(current->left);
                    if(print){ std::cout << current->left->ID << " "; }
                    from_q++;
                }
                if (current->right != nullptr && current->right->status == UNCHECKED) {
                    current->right->status = CHECKED;
                    q.push(current->right);
                    if(print){ std::cout << current->right->ID << " "; }
                    from_q++;
                }
            }
        }
        added.push_back(from_q);
        if(print){std::cout << std::endl; }
    }
    iterations--;
    return iterations;
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
    short min_time = UNASSIGNED;
    std::vector<short> min_id;

    for(short id = 1; id <= this->size; id++){
        short tmp = this->SendMessage(id, false);
        if(min_time == UNASSIGNED || tmp < min_time){
            min_time = tmp;
        }
    }
    for(short id = 1; id <= this->size; id++){
        short tmp = this->SendMessage(id, false);
        if(min_time == tmp){
            min_id.push_back(id);
        }
    }

    std::cout << "\n\tShortest time: " << min_time << " iterations on those IDS: ";
    for(short id : min_id){
        std::cout << id << " ";
    }
    std::cout << std::endl;

    std::cout << "\tShortest path example (" << "id:" << min_id.back()  << ")\n" << std::endl;
    this->SendMessage(min_id.back(), true);
    std::cout << "\tBest path selected from " << this->size << " different routes\n\n";
}