#include "graph.h"
#include "loadGraph.h"
#include "DFS_iter.cpp"

int main(int argc, char **argv){
    std::string path = argv[1];

    if (argc < 2){
        std::cerr << "You did not enter graph." << std::endl;
        exit(-1);
    }

    Graph graph = loadGraph(path);
    int nodes = GetNodeCount(path);

    std::cout << "There are " << nodes << " original nodes." << std::endl;
    //printGraph(graph);

    DFS dfs(graph);/*
    Graph tstg = graph;
    dfs.Reset(tstg);
*/    

    return 0;
}