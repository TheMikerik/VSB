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
#include "AbstractEmoloyee.h"
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
    std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n----=== SEMESTRAL PROJECT ===-----" << std::endl;
    std::cout << "             PIZZERIA\n\n\n\n\n\n\n\n\n" << std::endl;



//Pizzeria creation
    Pizzeria pepe("Pepe Pizza", 604505606, "www.pepepizza.cz");
    pepe.IntroducePizzeria();
    pepe.StopProgram();
//Employees added
    std::cout << "\nLets now add some employees" << std::endl;
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
    pepe.StopProgram();
//Employees print
    pepe.PrintEmployees();
    pepe.TestVirtual();
//Delivery and cook workers print
    pepe.PrintDelivery();
    pepe.PrintCook();
//Destructor test
    pepe.Deletion();
    pepe.MakeSpace();
    pepe.PrintCook();
    pepe.PrintDelivery();
    pepe.IntroducePizzeria();
    pepe.StopProgram();
//Add more employees
    std::cout << "\nLets add more employees" << std::endl;
    pepe.AddEmployee("Petr Novak", false, true);
    pepe.AddEmployee("Simon Novotny", false, false);
    pepe.AddEmployee("Ondrej Adamek", true, false);
    pepe.AddEmployee("David Nekonecny", true, true);
    pepe.AddEmployee("Ondrej Stein", false, false);
    pepe.AddEmployee("Antonin Horka", false, true);
    pepe.AddEmployee("Frantisek Pavel", true, false);
    pepe.AddEmployee("Tomas Smutny", true, false);
    pepe.AddEmployee("Jiri Vesely", false, false);
    pepe.AddEmployee("Vojtech Nord", false, false);
    pepe.AddEmployee("Petr Brzobohaty", false, true);
    pepe.AddEmployee("Jonas Pavlasek", true, false);
    pepe.AddEmployee("Michal Novak", true, true);
    pepe.PrintCook();
    pepe.PrintDelivery();
    pepe.IntroducePizzeria();
    pepe.StopProgram();
//Add stuff into menu
    std::cout << "\nLets add stuff into menu" << std::endl;
    std::cout << "  Pizzas:" << std::endl;
    pepe.menu.AddPizza("Chilli", 50, 30);
    pepe.menu.AddPizza("Sunkova", 60, 80);
    pepe.menu.AddPizza("Syrova", 80, 50);
    pepe.menu.AddPizza("Tvaruzkova", 90, 10);
    pepe.menu.AddPizza("Spenatova", 80, 50);
    pepe.menu.AddPizza("Smetanova", 90, 10);
    std::cout << "  Drinks:" << std::endl;
    pepe.menu.AddDrink("Fanta", 10, 5);
    pepe.menu.AddDrink("Cocacola", 20, 15);
    pepe.menu.AddDrink("Pepsi", 15, 2);
    pepe.menu.AddDrink("Malinovka", 11, 9);
    pepe.menu.PrintWholeMenu();



//Delete drinks and pizzas from menu
    pepe.menu.DeletionDrinks();
    pepe.menu.DeletionPizzas();
    pepe.menu.PrintWholeMenu();
    pepe.StopProgram();
//Adding stuff into menu
    std::cout << "\nLets add more stuff into menu:" << std::endl;
    std::cout << "  Pizzas:" << std::endl;
    pepe.menu.AddPizza("Chilli", 50, 30);
    pepe.menu.AddPizza("Vegetarianska", 60, 80);
    pepe.menu.AddPizza("Hermelinova", 80, 50);
    pepe.menu.AddPizza("Kureci", 90, 10);
    pepe.menu.AddPizza("Spenatova", 80, 50);
    pepe.menu.AddPizza("Kureci - special", 90, 10);
    std::cout << "  Drinks:" << std::endl;
    pepe.menu.AddDrink("Fanta", 10, 5);
    pepe.menu.AddDrink("Cocacola", 20, 15);
    pepe.menu.AddDrink("Pepsi", 15, 2);
    pepe.menu.AddDrink("Malinovka", 11, 9);
    pepe.menu.AddDrink("Mirinda", 10, 5);
    pepe.menu.AddDrink("Sprite", 20, 15);
    pepe.menu.AddDrink("Pepsi", 15, 2);
    pepe.menu.AddDrink("Malinovka", 11, 9);
    pepe.menu.PrintWholeMenu();
    pepe.StopProgram();

//Add customers
    std::cout << "\nLets add some customers:" << std::endl;
    pepe.AddCustomer("Pavla Novotna", "Standl 42");
    pepe.AddCustomer("Eliska Adamkova", "Frydek 89");
    pepe.AddCustomer("Petra Kocichova", "Sviadnov 403");
    pepe.AddCustomer("Ema Zla", "Paskov 5");
    pepe.AddCustomer("Petra Novotna", "Ostrava 16");
    pepe.AddCustomer("Natalie Jurickova", "Zlin 87");
    pepe.AddCustomer("Denisa Linhart", "Praha 456");
    pepe.PrintCustomers();
    pepe.IntroducePizzeria();
    pepe.StopProgram();
//Orders for customer
    std::cout << "\n\nLets add orders to customers:";
    pepe.OrderForCustomer(3);
    pepe.OrderForCustomer(2);
    pepe.OrderForCustomer(1);
    pepe.IntroducePizzeria();
    pepe.menu.PrintWholeMenu();
    pepe.StopProgram();

    std::cout << "Thats the very end of this project.\n\n" << std::endl;
    return 0;
}