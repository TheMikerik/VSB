// https://www.youtube.com/watch?v=mvbKAzt3W1s&ab_channel=JavaCodingInsightInterviewPreparation
#include "src/BinaryBalanced.h"
#include "src/BinaryBalanced.cpp"
#include "src/BinaryUnbalanced.h"
#include "src/BinaryUnbalanced.cpp"



int main(){

    std::string graph_path;

    for (int i = 1; i < 7; i++){
        switch(i){
            case 1:
                std::cout << "\n---------------------------------------------------------------------------" <<
                             "\n--------------------------GRAPH: graph-single.txt--------------------------" <<
                             "\n---------------------------------------------------------------------------";
                graph_path = "test_data/graph-single.txt";
                break;
            case 2:
                std::cout << "\n---------------------------------------------------------------------------" <<
                             "\n--------------------------GRAPH: graph-small-1.txt-------------------------" <<
                             "\n---------------------------------------------------------------------------";
                graph_path = "test_data/graph-small-1.txt";
                break;
            case 3:
                std::cout << "\n---------------------------------------------------------------------------" <<
                             "\n--------------------------GRAPH: graph-small-2.txt-------------------------" <<
                             "\n---------------------------------------------------------------------------";
                graph_path = "test_data/graph-small-2.txt";
                break;
            case 4:
                std::cout << "\n---------------------------------------------------------------------------" <<
                             "\n--------------------------GRAPH: graph-small-3.txt-------------------------" <<
                             "\n---------------------------------------------------------------------------";
                graph_path = "test_data/graph-small-3.txt";
                break;
            case 5:
                std::cout << "\n---------------------------------------------------------------------------" <<
                             "\n--------------------------GRAPH: graph-medium.txt--------------------------" <<
                             "\n---------------------------------------------------------------------------";
                graph_path = "test_data/graph-medium.txt";
                break;
            case 6:
                std::cout << "\n---------------------------------------------------------------------------" <<
                             "\n---------------------------GRAPH: graph-huge.txt---------------------------" <<
                             "\n---------------------------------------------------------------------------";
                graph_path = "test_data/graph-huge.txt";
                break;
            default:
                break;
        }

        BinaryBalanced balanced_tree;
        std::cout << "\n\n-----BALANCED TREE:";
        balanced_tree.LoadGraph(graph_path);
        balanced_tree.ShortestPath();

        std::cout << "\n-----UNBALANCED TREE:";
        BinaryUnbalanced unbalanced_tree;
        unbalanced_tree.LoadGraph(graph_path);
        unbalanced_tree.ShortestPath();
    }
    return 0;
}