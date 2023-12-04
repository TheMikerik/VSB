#pragma once
#include "Node.h"
#include <stack>
#include <queue>
#include <vector>
#include <fstream>

class BinaryUnbalanced{
private:
    short size;
    Node* Graph;
    std::stack<bool> path;

public:
    BinaryUnbalanced();
    ~BinaryUnbalanced();
    void DeleteGraph(Node* node);

    /**
     * Loads graph form input file
     * @param filename name of the input file
     */
    void LoadGraph(const std::string& filename);

    /**
     * Inserts a node into the Graph (UNBALANCED WAY = Binary Search Tree)
     * @param inp input number of the new node
     */
    void Insert(short inp);

    /**
     * Checks if the given node has some neighbors that has not been checked yet
     *
     * @param node Current node that should be checked
     * \retval TRUE unchecked neighbors do exist
     * \retval FALSE unchecked neighbors do not exist
     */
    bool CheckNearbyStatuses(Node* node);

    /**
     * Searches for a node with the given value
     * @param inp Seeked value
     * @return Pointer to searched node
     */
    Node* SearchNode(short inp);

    /**
    * Sends a message though the graph starting from the given node
    * @param print Prints each iteration (step) of the shortest path
    * @param start_number ID from which the path is starting
    * @return Time period for the message to travel trough the graph
    */
    short SendMessage(short inp, bool print);

    /**
     * Resets statuses of each node in the graph
     */
    void ResetStatuses();

    /**
     * Calculates the shortest time period for the message to travel over the graph
     */
    void ShortestPath();
};