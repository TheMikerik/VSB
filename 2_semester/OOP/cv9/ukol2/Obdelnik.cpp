#include "Obdelnik.h"
#include "GeometricObject.h"

Obdelnik::Obdelnik(int a, int b)
{
    this->stranaA = a;
    this->stranaB = b;
    this->type = "Obdelnik";

    this->VypocetObsahu();
    this->VypocetObvodu();
}

double Obdelnik::VypocetObvodu()
{
    this->obvod = this->stranaA * 2 + this->stranaB * 2;
    return this->obvod;
}

double Obdelnik::VypocetObsahu()
{
    this->obsah = this->stranaA * this->stranaB;
    return this->obsah;
}

std::string Obdelnik::Vypis()
{
    return "Object: " + this->type + " s hranou A " + std::__cxx11::to_string(this->stranaA) + " a B " + std::__cxx11::to_string(this->stranaB) +
    " obvod (" + std::__cxx11::to_string(this->obvod) + ")" + " + obsah (" + std::__cxx11::to_string(this->obsah) + ")";
}