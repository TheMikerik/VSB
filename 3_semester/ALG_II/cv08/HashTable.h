#ifndef ALG_II_HASHTABLE_H
#define ALG_II_HASHTABLE_H

#include <iostream>

template <typename T>

class HashTable {
public:
    HashTable(int size);
    void insert(int key, T value);
    T search(int key);
    bool remove(int key);
    void print();
};

#endif //ALG_II_HASHTABLE_H
