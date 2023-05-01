#pragma once
#include <string>
#include <iostream>

#include "Pizza.h"
#include "Drink.h"

#define MAX_P 10  //Maximum pizzas per order
#define MAX_D 5  //Maximum drinks per order


class Order{
private:
    static int static_order_ID;

    int order_ID;
    int pizzas_in_order;
    int drinks_in_order;

    Pizza* ordered_pizzas[MAX_P];
    Drink* ordered_drinks[MAX_D];
public:
    Order();
    ~Order();

    void AddPizza(Pizza* pizza);
    void AddDrink(Drink* drink);
    int GetPizzasInOrder();
    int GetDrinksInOrder();
    Pizza* GetPizza(int index);
    Drink* GetDrink(int index);
    int GetOrderID();
};