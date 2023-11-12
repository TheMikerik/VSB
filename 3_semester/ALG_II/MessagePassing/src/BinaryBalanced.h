#pragma once
#include "Node.h"
#include <stack>
#include <queue>
#include <vector>
#include <fstream>

class BinaryBalanced{
    private:
        short size;
        Node* Graph;
        std::stack<bool> path;

    public:
        BinaryBalanced();
        ~BinaryBalanced();

        /**
         * Loads graph form input file
         * @param filename name of the input file
         */
        void LoadGraph(const std::string& filename);

        /**
         * Inserts a node into the Graph (in a BALANCED way)
         * @param inp input number of the new node
         */
        void Insert(short inp);

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
        * Prints the shortest path for the message to travel all trough the graph
        * @param start_number ID from which the path is starting
        */
        short SendMessage(short start_id, bool print);

        /**
         * Resets statuses of each node in the graph
         */
        void ResetStatuses();

        /**
         * Calculates the shortest time for the message to travel
         */
        void ShortestPath();
};