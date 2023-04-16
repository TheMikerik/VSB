#pragma once
#include <string>
#include <iostream>

#include "Menu.h"

#define MAX_P 10  //Maximum pizzas per order
#define MAX_D 5  //Maximum drinks per order


class Order{
private:
    static int static_order_ID;

    int order_ID;
    int pizzas_in_order;
    int drinks_in_order;

    Menu* menu;

    Pizza* ordered_pizzas[MAX_P];
    Drink* ordered_drinks[MAX_D];
public:
    Order(Menu* menu);
    void AddPizza(int ID);
    void AddDrink(int ID);
    int GetOrderID();
};