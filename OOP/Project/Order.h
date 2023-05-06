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
    /**
     * @brief Order class constructor
    */
    Order();
    /**
     * @brief Order class destructor
    */
    ~Order();

    /**
     * @brief Adds pizza into order
     * @param pizza Pizza from the menu, that will be added into order 
    */
    void AddPizza(Pizza* pizza);
    /**
     * @brief Adds drink into order
     * @param drink Drink from the menu, that will be added into order 
    */
    void AddDrink(Drink* drink);
    /**
     * @return Total pizzas count in order 
    */
    int GetPizzasInOrder();
    /**
     * @return Total drinks count in order 
    */
    int GetDrinksInOrder();
    /**
     * @param index Index of the pizza in this exact order 
     * @return Pizza with selected index
    */
    Pizza* GetPizza(int index);
    /**
     * @param index Index of the drink in this exact order
     * @return Drink with selected index 
    */
    Drink* GetDrink(int index);
    /**
     * @return ID of this exact order
    */
    int GetOrderID();
};