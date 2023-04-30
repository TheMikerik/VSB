#include "graph.h"
#include "loadGraph.h"
#include "DFS_iter.cpp"

int main(int argc, char **argv){
/*
    if (argc < 2){
        std::cerr << "You did not enter graph." << std::endl;
        exit(-1);
    }
*/
    for (int in=1; in<6; in++){
        std::string path = "Graph" + std::to_string(in) + ".txt";
        Graph graph = loadGraph(path);
        DFS dfs(graph);

        std::cout << path << " has " << graph.count << " original nodes." << std::endl;
        printGraph(graph);

        dfs.Reset(graph);   
        dfs.PrintInfo();
        dfs.DoDFS();

        std::cout << "\n\n\n\n\n\n";
    }

    return 0;
}