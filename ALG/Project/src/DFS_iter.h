#pragma once

#include "graph.h"

class DFS{
        Graph graph;

        int noNodes;
    public:
        DFS(Graph gra);
        ~DFS();

        std::vector<int> Reset(Graph testGraph);   //Vrati pocatecni hodnoty v kazde komponente
        /*
        void Next();
        void IsEnd();
        void CurrentKey();*/
};