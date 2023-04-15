#include <string>
#include <iostream>
#include "Pizzeria.h"
#include "Pizzeria.cpp"
#include "Employee.h"
#include "Employee.cpp"
#include "Delivery.h"
#include "Delivery.cpp"
#include "Cook.h"
#include "Cook.cpp"

int main (){
    std::cout << "----=== SEMESTRAL PROJECT ===-----" << std::endl;
    std::cout << "             PIZZERIA" << std::endl;



//Pizzeria creation
    Pizzeria pepe("Pepe Pizza", 604505606, "www.pepepizza.cz");
    pepe.IntroducePizzeria();
//Employees added
    std::cout << "Lets now add some employees" << std::endl;
    pepe.AddEmployee("Michal Rucka", false, true);
    pepe.AddEmployee("Jan Novak", false, false);
    pepe.AddEmployee("Marek Zacek", true, false);
    pepe.AddEmployee("Rostislav Vrana", true, true);
    pepe.AddEmployee("David Vavra", true, false);
    pepe.AddEmployee("Matej Chovanec", false, true);
    pepe.AddEmployee("Vilem Zamboch", true, false);
    pepe.AddEmployee("Ctibor Matlak", false, true);
    pepe.AddEmployee("Petr Novotny", false, false);
    pepe.AddEmployee("Lukas Stefek", false, true);
    pepe.AddEmployee("Simon Svarny", true, false);
    pepe.AddEmployee("David Dvorsky", true, true);
    pepe.IntroducePizzeria();
//Employees print
    pepe.PrintEmployees();
//Delivery and cook workers print
    pepe.PrintDelivery();
    pepe.PrintCook();

    std::cout << "\n\n" << std::endl;
    return 0;
}