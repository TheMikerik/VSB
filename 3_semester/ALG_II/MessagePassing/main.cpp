// https://www.youtube.com/watch?v=mvbKAzt3W1s&ab_channel=JavaCodingInsightInterviewPreparation
#include "src/BinaryBalanced.h"
#include "src/BinaryBalanced.cpp"
//#include "src/BinaryRandom.h"
//#include "src/BinaryRandom.cpp"



int main(){

    std::string graph_path;

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

        BinaryBalanced balanced_tree;
        balanced_tree.LoadGraph(graph_path);
        balanced_tree.ShortestPath();

//        BinaryRandom random_tree;
//        random_tree.LoadGraph(graph_path);
//        random_tree.ShortestPath();

    }
    return 0;
}