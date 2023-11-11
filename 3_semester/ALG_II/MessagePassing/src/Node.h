#pragma once
#include <iostream>

enum {
    UNCHECKED = false,
    CHECKED = true
};

struct Node {
    short value;
    short ID;
    bool status;
    Node *parent;
    Node *left;
    Node *right;

    Node(short value, short id) {
        this->value = value;
        this->ID = id;
        this->status = UNCHECKED;
        this->parent = nullptr;
        this->left = nullptr;
        this->right = nullptr;
    }
    Node(short value, short id, Node *parent) {
        this->value = value;
        this->ID = id;
        this->status = UNCHECKED;
        this->parent = parent;
        this->left = nullptr;
        this->right = nullptr;
    }
};
