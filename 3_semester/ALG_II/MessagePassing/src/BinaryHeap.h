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

        /**
         * Inserts a node into the Graph
         * @param inp input number of the new node
         */
        void Insert(short inp);

        /**
         * Searches for a node in the Graph
         * @param inp seeked number value
         * @return ID of the found node
         */
        short SearchNodeID(short inp);

        /**
         * Fills the path vector with the path from the root to the node
         * @param id_destination ID of the destination node
         */
        void GetPathFrom(short id_destination);

        bool CheckNearbyStatuses(Node* node);
        void SendMessage(short start_number);
};