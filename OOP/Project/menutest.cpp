#include <string>
#include <iostream>

#include "Drink.h"
#include "Drink.cpp"
#include "Pizza.h"
#include "Pizza.cpp"
#include "Menu.h"
#include "Menu.cpp"

int main(){
    Menu menu;
    menu.AddPizza("Chilli", 50, 30);
    menu.AddPizza("Sunkova", 60, 80);
    menu.AddPizza("Syrova", 80, 50);
    menu.AddPizza("Tvaruzkova", 90, 10);
    menu.AddPizza("Spenatova", 80, 50);
    menu.AddPizza("Smetanova", 90, 10);
    menu.AddDrink("Fanta", 10, 5);
    menu.AddDrink("Cocacola", 20, 15);
    menu.AddDrink("Pepsi", 15, 2);
    menu.AddDrink("Malinovka", 11, 9);
    menu.PrintWholeMenu();
    menu.DeletionDrinks();
    menu.DeletionPizzas();
    menu.PrintWholeMenu();


    return 0;
}