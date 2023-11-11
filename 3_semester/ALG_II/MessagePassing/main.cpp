// https://www.youtube.com/watch?v=mvbKAzt3W1s&ab_channel=JavaCodingInsightInterviewPreparation
#include "src/BinaryHeap.h"
#include "src/BinaryHeap.cpp"

#include <vector>

int main(){
    BinaryHeap tree((short)1);

   for(short i = 2; i <= 32; i++){
       tree.Insert(i);
   }

   tree.SearchNode(5);
   tree.SearchNode(10);
   tree.SearchNode(150);

    return 0;
}