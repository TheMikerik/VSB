#include "BinaryRandom.h"

BinaryRandom::BinaryRandom(){
    this->size = 0;
    this->Graph = nullptr;
}

BinaryRandom::~BinaryRandom(){
    delete this->Graph;
}

void BinaryRandom::LoadGraph(const std::string& filename){
    short number;
    std::ifstream infile(filename);

    while(!infile.eof()) {
        infile >> number;
        this->Insert(number);
    }

    infile.close();
}

void BinaryRandom::Insert(short inp) {
    if (this->Graph == nullptr) {
        this->size++;
        this->Graph = new Node(inp, this->size);
    } else {
        this->size++;

        Node *current = this->Graph;
        while (true) {
            bool goLeft = std::rand() % 8 == 0;
            if (goLeft) {
                if (current->left == nullptr) {
                    current->left = new Node(inp, size, current);
                    break;
                } else {
                    current = current->left;
                }
            } else {
                if (current->right == nullptr) {
                    current->right = new Node(inp, size, current);
                    break;
                } else {
                    current = current->right;
                }
            }
        }
    }
}


bool BinaryRandom::CheckNearbyStatuses(Node *node) {
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

Node* BinaryRandom::SearchNode(short inp) {
    this->ResetStatuses();

    Node *current = this->Graph;
    std::queue<Node*> q;
    q.push(current);
    current->status = CHECKED;
    while(!q.empty()){
        current = q.front();
        q.pop();
        if (current->value == inp){ return current; }

        if(current->left != nullptr && current->left->status == UNCHECKED){
            q.push(current->left);
            current->left->status = CHECKED;
        }
        if(current->right != nullptr && current->right->status == UNCHECKED) {
            q.push(current->right);
            current->right->status = CHECKED;
        }
    }
    std::cerr << "Node not found!" << std::endl;
    return nullptr;
}

short BinaryRandom::SendMessage(short inp) {
    Node *current = this->SearchNode(inp);

    this->ResetStatuses();
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

void BinaryRandom::SendMessagePrint(short inp) {
    Node *current = this->SearchNode(inp);

    this->ResetStatuses();
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

void BinaryRandom::ResetStatuses(){
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

void BinaryRandom::ShortestPath(){

    std::vector<Node*> starters;

    Node* start = this->Graph;
    std::queue<Node*> q;
    q.push(start);
    start->status = CHECKED;

    starters.push_back(start);

    while(!q.empty()){
        start = q.front();
        q.pop();
        if(start->left != nullptr && start->left->status == UNCHECKED){
            q.push(start->left);
            starters.push_back(start->left);
            start->left->status = CHECKED;
        }
        if(start->right != nullptr && start->right->status == UNCHECKED) {
            q.push(start->right);
            starters.push_back(start->right);
            start->right->status = CHECKED;
        }
    }

    short min_time = -1;
    std::vector<short> min_values;
    short i = 0;

    for(Node* s : starters){
        short tmp = this->SendMessage(s->value);

        if(min_time == -1 || min_time >= tmp){
            min_time = tmp;
            min_values.push_back(s->value);
        }
        i++;
    }

    std::cout << "\nShortest time: " << min_time << " iterations with those values: ";
    for(short id : min_values){
        std::cout << id << " ";
    }
    std::cout << std::endl;

    std::cout << "Shortest path example (" << "value:" << min_values.back()  << ")\n" << std::endl;
    this->SendMessagePrint(min_values.back());
    std::cout << "Checked " << i << " different routes\n\n";
}