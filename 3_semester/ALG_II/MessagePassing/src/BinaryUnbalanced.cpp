#include "BinaryUnbalanced.h"

BinaryUnbalanced::BinaryUnbalanced(){
    this->size = 0;
    this->Graph = nullptr;
}

BinaryUnbalanced::~BinaryUnbalanced() {
    if (this->Graph != nullptr) {
        this->DeleteGraph(this->Graph);
        this->Graph = nullptr;
    }
}

void BinaryUnbalanced::DeleteGraph(Node* node) {
    if (node != nullptr) {
        this->DeleteGraph(node->left);
        this->DeleteGraph(node->right);
        delete node;
    }
}

void BinaryUnbalanced::LoadGraph(const std::string& filename){
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

void BinaryUnbalanced::Insert(short inp) {
    if (this->Graph == nullptr) {
        this->size++;
        this->Graph = new Node(inp, this->size);
    } else {
        this->size++;

        Node *current = this->Graph;
        while (true) {
            if (inp < current->value) {
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


bool BinaryUnbalanced::CheckNearbyStatuses(Node *node) {
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

Node* BinaryUnbalanced::SearchNode(short inp) {
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

short BinaryUnbalanced::SendMessage(short inp, bool print) {
    Node *current = this->SearchNode(inp);

    this->ResetStatuses();

    std::queue<Node*> q;
    current->status = CHECKED;
    q.push(current);
    short from_q = 1;
    short iterations = 0;

    std::vector<short> added;
    added.push_back(from_q);

    if(print){ std::cout << "\tStarting from: " << current->value << std::endl; }
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
                    if(print){ std::cout << current->parent->value << " ";}
                    from_q++;
                }
                if (current->left != nullptr && current->left->status == UNCHECKED) {
                    current->left->status = CHECKED;
                    q.push(current->left);
                    if(print){ std::cout << current->left->value << " ";}
                    from_q++;
                }
                if (current->right != nullptr && current->right->status == UNCHECKED) {
                    current->right->status = CHECKED;
                    q.push(current->right);
                    if(print){ std::cout << current->right->value << " ";}
                    from_q++;
                }
            }
        }
        added.push_back(from_q);
        if(print){ std::cout << std::endl;}
    }
    iterations--;
    return iterations;
}

void BinaryUnbalanced::ResetStatuses(){
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

void BinaryUnbalanced::ShortestPath(){

    std::vector<Node*> starters;

    this->ResetStatuses();
    Node* s_nodes = this->Graph;
    std::queue<Node*> q;
    q.push(s_nodes);
    s_nodes->status = CHECKED;

    starters.push_back(s_nodes);

    while(!q.empty()){
        s_nodes = q.front();
        q.pop();
        if(s_nodes->left != nullptr && s_nodes->left->status == UNCHECKED){
            q.push(s_nodes->left);
            starters.push_back(s_nodes->left);
            s_nodes->left->status = CHECKED;
        }
        if(s_nodes->right != nullptr && s_nodes->right->status == UNCHECKED) {
            q.push(s_nodes->right);
            starters.push_back(s_nodes->right);
            s_nodes->right->status = CHECKED;
        }
    }

    short min_time = UNASSIGNED;
    std::vector<short> min_values;
    short no_nodes = 0;

    for(Node* s : starters){
        short tmp = this->SendMessage(s->value, false);
        if(min_time == UNASSIGNED || tmp < min_time){
            min_time = tmp;
        }
        no_nodes++;
    }
    for(Node* s : starters){
        short tmp = this->SendMessage(s->value, false);
        if(min_time == tmp){
            min_values.push_back(s->value);
        }
    }

    std::cout << "\n\tShortest time: " << min_time << " iterations with those values: ";
    for(short val : min_values){
        std::cout << val << " ";
    }
    std::cout << std::endl;

    std::cout << "\tShortest path example (" << "value:" << min_values.back()  << ")\n" << std::endl;
    this->SendMessage(min_values.back(), true);
    std::cout << "\tBest path selected from " << no_nodes << " different routes\n\n";
}