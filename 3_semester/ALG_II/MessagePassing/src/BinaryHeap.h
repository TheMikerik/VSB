#pragma once
#include "Node.h"
#include <stack>
#include <queue>
#include <vector>
#include <fstream>

enum{
    LEFT = true,
    RIGHT = false,

    RANDOM = true,
    BALANCED = false
};

class BinaryHeap{
    private:
        short size;
        Node* Graph;
        std::stack<bool> path;

    public:
        BinaryHeap();
        ~BinaryHeap();

        /**
         * Loads graph form input file
         * @param filename name of the input file
         * @param style true if random, false if balanced
         */
        void LoadGraph(const std::string& filename, bool style);

        /**
         * Inserts a node into the Graph (in a BALANCED way)
         * @param inp input number of the new node
         */
        void InsertBalanced(short inp);

        /**
         * Inserts a node into the Graph (in a RANDOM way)
         * @param inp input number of the new node
         */
        void InsertRandom(short inp);

        /**
         * Fills the path vector with the path from the root to the node
         * @param id_destination ID of the destination node
         */
        void GetPathFrom(short id_destination);

        /**
         * Checks if the given node has some neighbors that has not been checked
         *
         * @param node Current node that should be checked
         * \retval TRUE unchecked neighbors do exist
         * \retval FALSE unchecked neighbors do not exist
         */
        bool CheckNearbyStatuses(Node* node);

        /**
         * Calculates the time for the message to travel all trough the graph
         * @param start_number ID from which the path should be calculated
         * @return Shortest time to travel all trough the graph
         */
        short SendMessage(short start_id);

        /**
        * Prints the shortest path for the message to travel all trough the graph
        * @param start_number ID from which the path is starting
        */
        void SendMessagePrint(short start_id);

        /**
         * Resets statuses of each node in the graph
         */
        void ResetStatuses();

        /**
         * Calculates the shortest time for the message to travel
         */
        void ShortestPath();
};