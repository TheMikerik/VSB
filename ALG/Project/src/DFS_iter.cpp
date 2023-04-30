#include "DFS_iter.h"

DFS::DFS(Graph gra){
    this->graph = gra;
}
DFS::~DFS(){
    delete this->graph.nodes;
}

std::vector<int> DFS::Reset(Graph testGrap){

    std::vector<int> start_in_components;

    for (int i=0; i<testGrap.count; i++){
        if (testGrap.nodes[i].status == UNCHECKED){
            Node* currentNode = &testGrap.nodes[i];

            int lowest = currentNode->id;
            
            std::stack<Node *> stack;
            stack.push(currentNode);
            currentNode->status = CHECKING;

            while( !stack.empty() ){
                Node* currentNode = stack.top();
                stack.pop();

                if (currentNode->id < lowest){
                    lowest = currentNode->id;
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
            std::cout << lowest << " ";
        }
    }

    return start_in_components;
}