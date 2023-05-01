#include "Ctverec.h"

Ctverec::Ctverec(double s) : GeometricObject()
{
    this->strana = s;
    this->type = "Ctverec";
    
    this->VypocetObsahu();
    this->VypocetObvodu();
}

double Ctverec::VypocetObsahu()
{
    this->obsah = this->strana * this->strana;
    return this->obsah;
}

double Ctverec::VypocetObvodu()
{
    this->obvod = this->strana * 4;
    return this->obvod;
}

std::string Ctverec::Vypis()
{
    return "Object: " + this->type + " s hranou " + std::to_string(this->strana) +
    " obvod (" + std::to_string(this->obvod) + ")" + " + obsah (" + std::to_string(this->obsah) + ")";
}