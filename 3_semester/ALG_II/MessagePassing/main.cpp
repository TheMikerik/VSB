// https://www.youtube.com/watch?v=mvbKAzt3W1s&ab_channel=JavaCodingInsightInterviewPreparation
#include "src/BinaryHeap.h"
#include "src/BinaryHeap.cpp"



int main(){

    std::string graph_path;
    short start;

    for (int i = 1; i < 5; i++){
        switch(i){
            case 1:
                std::cout << "\n---------------------------------------------------" <<
                             "\n--------------GRAPH: graph-single.txt--------------" <<
                             "\n---------------------------------------------------";
                graph_path = "test_data/graph-single.txt";
                break;
            case 2:
                std::cout << "\n---------------------------------------------------" <<
                             "\n---------------GRAPH: graph-small.txt--------------" <<
                             "\n---------------------------------------------------";
                graph_path = "test_data/graph-small.txt";
                break;
            case 3:
                std::cout << "\n---------------------------------------------------" <<
                             "\n--------------GRAPH: graph-medium.txt--------------" <<
                             "\n---------------------------------------------------";
                graph_path = "test_data/graph-medium.txt";
                break;
            case 4:
                std::cout << "\n---------------------------------------------------" <<
                             "\n---------------GRAPH: graph-huge.txt---------------" <<
                             "\n---------------------------------------------------";
                graph_path = "test_data/graph-huge.txt";
                break;
            default:
                break;
        }

        BinaryHeap tree;

        // Choose one
        //tree.LoadGraph(graph_path, BALANCED);
        tree.LoadGraph(graph_path, RANDOM);

        tree.ShortestPath();

    }
    return 0;
}