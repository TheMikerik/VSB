#pragma once
#include "GeometricObject.h"

class Obdelnik : public GeometricObject
{
private:
    int stranaA;
    int stranaB;

public:
    Obdelnik(int a, int b);

    double VypocetObvodu();
    double VypocetObsahu();
    virtual std::string Vypis();
};