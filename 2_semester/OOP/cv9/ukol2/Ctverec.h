#pragma once

#include "GeometricObject.h"

class Ctverec : public GeometricObject
{
private:
    int strana;

public:
    Ctverec(double s);

    double VypocetObvodu();
    double VypocetObsahu();
    virtual std::string Vypis();
};