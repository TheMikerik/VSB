#include "Kruh.h"
#include "GeometricObject.h"

Kruh::Kruh(int r) : GeometricObject()
{
    this->polomer = r;
    this->type = "Kruh";

    this->VypocetObsahu();
    this->VypocetObvodu();
}

double Kruh::VypocetObsahu()
{
    this->obsah = this->polomer * this->polomer * 3.1415;
    return this->obsah;
}

double Kruh::VypocetObvodu()
{
    this->obvod = this->polomer * 2 * 3.1415;
    return this->obvod;
}

std::string Kruh::Vypis()
{
    return "Object: " + this->type + " s polomerem " + std::to_string(this->polomer) +
    " obvod (" + std::to_string(this->obvod) + ")" + " + obsah (" + std::to_string(this->obsah) + ")";
}