#include <iostream>
#include <string>
#include "GeometricObject.cpp"
#include "Ctverec.cpp"
#include "Kruh.cpp"
#include "Obdelnik.cpp"

int main()
{
    GeometricObject *o1 = new Obdelnik(18, 64);
    GeometricObject *o2 = new Kruh(1);
    GeometricObject *o3 = new Kruh(7);
    GeometricObject *o4 = new Ctverec(8);
    GeometricObject *o5 = new Ctverec(5);
    GeometricObject *o6 = new Obdelnik(2, 15);
    GeometricObject *o7 = new Kruh(4);
    GeometricObject *o8 = new Obdelnik(3, 7);

    GeometricObject** variable[8];

    variable[0] = &o1;
    variable[1] = &o2;
    variable[2] = &o3;
    variable[3] = &o4;
    variable[4] = &o5;
    variable[5] = &o6;
    variable[6] = &o7;
    variable[7] = &o8;

    for (int i=0; i<8; i++){
        std::cout << "     " << i << ". " << (*static_cast<GeometricObject*>(*variable[i])).Vypis() << std::endl;
    }

    return 0;
}