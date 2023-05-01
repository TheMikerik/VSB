#pragma once

#include <iostream>
#include <string>

class GeometricObject
{
public:
    std::string type;
    int obvod, obsah;

    double VypocetObsahu();
    double VypocetObvodu();

    virtual std::string Vypis() = 0;
};