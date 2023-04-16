#include <string>
#include <iostream>

#include "Drink.h"
#include "Drink.cpp"
#include "Pizza.h"
#include "Pizza.cpp"
#include "Menu.h"
#include "Menu.cpp"
#include "Pizzeria.h"
#include "Pizzeria.cpp"
#include "Employee.h"
#include "Employee.cpp"
#include "Delivery.h"
#include "Delivery.cpp"
#include "Cook.h"
#include "Cook.cpp"
#include "Customer.h"
#include "Customer.cpp"
#include "Order.h"
#include "Order.cpp"

int main (){
    std::cout << "----=== SEMESTRAL PROJECT ===-----" << std::endl;
    std::cout << "             PIZZERIA" << std::endl;



//Pizzeria creation
    Pizzeria pepe("Pepe Pizza", 604505606, "www.pepepizza.cz");
    pepe.IntroducePizzeria();
//Add customers
    std::cout << "\nLets add some customers" << std::endl;
    pepe.AddCustomer("Monika Ulrichova", "Standl 42");
    pepe.AddCustomer("Barbora Adamcova", "Frydek 89");
    pepe.AddCustomer("Anna Bilska", "Sviadnov 403");
    pepe.AddCustomer("Dorota Krecmerova", "Paskov 5");
    pepe.AddCustomer("Petra Novotna", "Ostrava 16");
    pepe.AddCustomer("Natalie Jurickova", "Zlin 87");
    pepe.AddCustomer("Denisa Mackova", "Praha 456");
    pepe.PrintCustomers();
    pepe.IntroducePizzeria();
    pepe.OrderForCustomer(3);
    /*
    pepe.GetCustomer(2)->CreateOrder();
    pepe.GetCustomer(3)->CreateOrder();
    pepe.GetCustomer(1)->CreateOrder();
    pepe.GetCustomer(2)->CreateOrder();
    */
    pepe.IntroducePizzeria();

    std::cout << "\n\n" << std::endl;
    return 0;
}