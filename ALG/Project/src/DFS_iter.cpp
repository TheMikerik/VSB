#include "DFS_iter.h"


static int iterator = 0;

DFS::DFS(Graph gra){
    this->graph = gra;
    this->isEnd = false;
    iterator = 0;
}
void DFS::PrintInfo(){
    std::cout << "This graph is divided into " << this->numberOfComponents << " components and their starting points are:" << std::endl;
    for (int i=1; i<this->startingComponents.size() + 1; i++){
        std::cout << "     " << i << ". component: " << startingComponents[i-1]->id << std::endl;
    } 
}
void DFS::ResetStatuses(){
    for (int i=0; i<this->graph.count; i++){
        this->graph.nodes[i].status = UNCHECKED;
    }
}
void DFS::Reset(Graph testGrap){

    std::vector<Node *> start_in_components;

    for (int i=0; i<testGrap.count; i++){
        if (testGrap.nodes[i].status == UNCHECKED){
            Node* currentNode = &testGrap.nodes[i];

            Node* lowest = currentNode;
            
            std::stack<Node *> stack;
            stack.push(currentNode);
            currentNode->status = CHECKING;

            while( !stack.empty() ){
                Node* currentNode = stack.top();
                stack.pop();

                if (currentNode->id < lowest->id){
                    lowest->id = currentNode->id;
                }

                for (std::vector<Node *>::size_type j=0; j<currentNode->neighbors.size(); j++){
                    if( currentNode->neighbors[j]->status == UNCHECKED ){
                        stack.push(currentNode->neighbors[j]);
                        currentNode->neighbors[j]->status = CHECKING;
                    }
                }
                currentNode->status = CHECKED;
            }

            start_in_components.push_back(lowest);
        }
    }

    this->numberOfComponents = start_in_components.size();
    this->startingComponents = start_in_components;
    this->ResetStatuses();
}
void DFS::CurrentKey(int id){
    std::cout << "     " << iterator << ". " << id << " " << std::endl;
    iterator++;
}
bool DFS::IsEnd(std::stack<Node *> st){
    if ( st.empty()){
        isEnd = true;
    } 

    return this->isEnd;
}
void DFS::DoDFS(){
    this->ResetStatuses();
    int iterator = 0;

    std::cout << "\nDepth First Search:" << std::endl;
    for (int j=1; j<this->startingComponents.size() + 1; j++){
        std::cout << j <<". component and iterator over it:" << std::endl;
        
        std::stack<Node *> stack;
        Node* current = this->startingComponents[j-1];
        stack.push(current);
        current->status = CHECKING;

        while ( !IsEnd(stack) ){
            Node* currentInLoop = stack.top();
            stack.pop();

            this->CurrentKey(currentInLoop->id);

            for (std::vector<Node *>::size_type i=0; i<currentInLoop->neighbors.size(); i++){
                if(currentInLoop->neighbors[i]->status == UNCHECKED){
                    stack.push(currentInLoop->neighbors[i]);
                    currentInLoop->neighbors[i]->status = CHECKING;
                }
            }
            currentInLoop->status = CHECKED;           
        }
        this->isEnd = false;
    }
}