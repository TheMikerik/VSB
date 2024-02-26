#include <iostream>

struct Bittfiels {
    char a : 3;
    char b : 3;
};

union Union {
    std::string str;
    int i;
};

class A {

};

class B : public A {

};