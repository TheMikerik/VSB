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
    Pizza(std::string nam, int cost, int prof);
    ~Pizza();

    void SetPizzaID(int id);

    std::string GetPizzaName();
    int GetPizzaPrice();
    int GetPizzaProfit();
    int GetPizzaID();
    int GetStaticID();
};