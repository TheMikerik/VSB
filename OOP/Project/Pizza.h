#pragma once
#include <string>
#include <iostream>

class Pizza{
protected:
    std::string pizza_name;
    int cost;
    int profit;
    int pizza_ID;

    static int static_pizzaID;
public:
    /**
     * @brief Pizza class constructor
     * @param nam Name of the pizza
     * @param cost Cost of the pizza
     * @param prof Pizzeria's profit on this pizza 
    */
    Pizza(std::string nam, int cost, int prof);
    /**
     * @brief Pizzeria class destructor 
    */
    ~Pizza();
    /**
     * @brief Set this pizza ID
     * @param id New pizza's ID
    */
    void SetPizzaID(int id);

    /**
     * @return This pizza's name 
    */
    std::string GetPizzaName();
    /**
     * @return This pizza's price 
    */
    int GetPizzaPrice();
    /**
     * @return This pizza's profit 
    */
    int GetPizzaProfit();
    /**
     * @return This pizza's ID 
    */
    int GetPizzaID();
    /**
     * @return Static pizzas ID 
    */
    int GetStaticID();
};