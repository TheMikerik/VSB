#pragma once
#include "loadGraph.h"

class DFS{
    private:
        Graph graph;
        int numberOfComponents;
        std::vector<Node *> startingComponents;
        bool isEnd;
    public:
        DFS(Graph gra);
        void PrintInfo();
        void ResetStatuses();
        
        void Reset(Graph testGrap);
        void CurrentKey(int id);
        bool IsEnd(std::stack<Node *> st);
        void DoDFS();
};
