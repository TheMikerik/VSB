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
//Employees print
    pepe.PrintEmployees();
//Delivery and cook workers print
    pepe.PrintDelivery();
    pepe.PrintCook();
//Destructor test
    pepe.Deletion();
    pepe.PrintCook();
    pepe.PrintDelivery();
    pepe.IntroducePizzeria();
//Add more employees
    std::cout << "\nLets add more employees" << std::endl;
    pepe.AddEmployee("David Spurek", false, true);
    pepe.AddEmployee("Simon Rodek", false, false);
    pepe.AddEmployee("Ondrej Slama", true, false);
    pepe.AddEmployee("David Koneny", true, true);
    pepe.AddEmployee("Ondrej Buzga", true, false);
    pepe.AddEmployee("Antonin Pustejovsky", false, true);
    pepe.AddEmployee("Frantisek Rucka", true, false);
    pepe.AddEmployee("Tomas Mer", true, false);
    pepe.AddEmployee("Jiri Prokel", false, true);
    pepe.AddEmployee("Vojtech Kicom", false, false);
    pepe.AddEmployee("Petr Brzobohaty", false, true);
    pepe.AddEmployee("Jonas Hlosta", true, false);
    pepe.AddEmployee("Michal Novak", true, true);
    pepe.PrintCook();
    pepe.PrintDelivery();
    pepe.IntroducePizzeria();

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
    pepe.menu.DeletionDrinks();
    pepe.menu.DeletionPizzas();
    pepe.menu.PrintWholeMenu();
    std::cout << "\nLets test if the ID doesnt repeat" << std::endl;
    std::cout << "  Pizzas:" << std::endl;
    pepe.menu.AddPizza("Chilli", 50, 30);
    pepe.menu.AddPizza("Sunkovaa", 60, 80);
    pepe.menu.AddPizza("Syrovaa", 80, 50);
    pepe.menu.AddPizza("Tvaruzkova", 90, 10);
    pepe.menu.AddPizza("Spenatovea", 80, 50);
    pepe.menu.AddPizza("Smetanova", 90, 10);
    std::cout << "  Drinks:" << std::endl;
    pepe.menu.AddDrink("Fanta", 10, 5);
    pepe.menu.AddDrink("Cocsacola", 20, 15);
    pepe.menu.AddDrink("Pepsi", 15, 2);
    pepe.menu.AddDrink("Malinovka", 11, 9);
    pepe.menu.AddDrink("Fantaaa", 10, 5);
    pepe.menu.AddDrink("Cocsacola", 20, 15);
    pepe.menu.AddDrink("Pepsi", 15, 2);
    pepe.menu.AddDrink("Malinovka", 11, 9);
    pepe.menu.PrintWholeMenu();


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
    pepe.OrderForCustomer(2);
    pepe.OrderForCustomer(1);
    pepe.OrderForCustomer(2);


    std::cout << "\n\n" << std::endl;
    return 0;
}