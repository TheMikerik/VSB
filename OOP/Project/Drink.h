#pragma once
#include <string>
#include <iostream>

class Drink{
protected:
    std::string drink_name;
    int cost;
    int profit;
    int drink_ID;

    static int static_drinkID;
public:
    Drink(std::string nam, int cost, int prof);
    ~Drink();

    void SetDrinkID(int id);

    std::string GetDrinkName();
    int GetDrinkPrice();
    int GetDrinkProfit();
    int GetDrinkID();
    int GetStaticID();
};