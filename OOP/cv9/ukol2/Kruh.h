#pragma once

#include "GeometricObject.h"

class Kruh : public GeometricObject
{
private:
    int polomer;
    float obvod, obsah;

public:
    Kruh(int p);

    double VypocetObvodu();
    double VypocetObsahu();
    virtual std::string Vypis();
};