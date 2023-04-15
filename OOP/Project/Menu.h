#pragma once
#include <string>
#include <iostream>
#include <vector>

#include "Pizza.h"
#include "Drink.h"

#define DRI 10
#define PIZ 10

class Menu{
protected:
    int stuff_in_menu;

    int drinks_count;
    int pizzas_count;

    Drink* drinks[DRI];
    Pizza* pizzas[PIZ];
public:
    Menu();
    ~Menu();

    void AddDrink(std::string nam, int cst, int prof);
    void AddPizza(std::string nam, int cst, int prof);
    void RemoveDrink(int id);
    void RemovePizza(int id);

    Drink* GetDrink(int id);
    Pizza* GetPizza(int id);
    int GetDrinksCount();
    int GetPizzasCount();
    int GetDrinkIndex(int id);
    int GetPizzaIndex(int);

    void PrintWholeMenu();
    void DeletionDrinks();
    void DeletionPizzas();
};