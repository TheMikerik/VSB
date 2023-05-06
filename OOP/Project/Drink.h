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
    /**
     * @brief Drink class constructor
     * 
     * @param nam Name of the drink
     * @param cost Price of the drink
     * @param prof Profit that pizzeria make every time they sell this product
    */
    Drink(std::string nam, int cost, int prof);
    /**
     * @brief Drink class destructor
    */
    ~Drink();
    
    /**
     * @brief Sets ID to selected drink
     * @param id New ID of the drink
    */
    void SetDrinkID(int id);

    /**
     * @return Name of the drink
    */
    std::string GetDrinkName();
    /**
     * @brief Returns price of the drink
    */
    int GetDrinkPrice();
    /**
     * @brief Returns profit that pizzeria make on this exact drink
    */
    int GetDrinkProfit();
    /**
     * @brief Returns ID of the drink
    */
    int GetDrinkID();
    /**
     * @brief Returns static ID of the drinks
    */
    int GetStaticID();
};