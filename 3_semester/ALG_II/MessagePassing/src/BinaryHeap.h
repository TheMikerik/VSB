#pragma once
#include "Node.h"
#include <stack>
#include <queue>

enum{
    LEFT = true,
    RIGHT = false
};

class BinaryHeap{
    private:
        short size;
        Node* Graph;
        std::stack<bool> path;

    public:
        explicit BinaryHeap(short inp);
        ~BinaryHeap();

        void Insert(short inp);

        short SearchNode(short inp);
        bool GetPathFrom(short destination);
        void SendMessage(short start_number);
};