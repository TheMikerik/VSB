#pragma once
#include <string>
#include <iostream>
#include <vector>

#include "Pizza.h"
#include "Drink.h"

#define DRI 10
#define PIZ 20

class Menu{
protected:
    int stuff_in_menu;

    int drinks_count;
    int pizzas_count;

    Drink* drinks[DRI];
    Pizza* pizzas[PIZ];
public:
    /**
     * @brief Menu class constructor
    */
    Menu();
    /**
     * @brief Menu class destructor
    */
    ~Menu();

    /**
     * @brief Adds drink into menu
     * 
     * Checks if drink is already in the menu and also
     * if the total drinks number is lower than possible.
     * If conditions are met, then it adds this drink into menu.
     * 
     * @param nam Name of the drink
     * @param cst Cost of the drink
     * @param prof Profit pizzeria make on this drink
    */
    void AddDrink(std::string nam, int cst, int prof);

    /**
     * @brief Adds pizza into menu
     * 
     * Checks if pizza is already in the menu and also
     * if the total pizzas number is lower than possible.
     * If conditions are met, then it adds this pizza into menu.
     * 
     * @param nam Name of the pizza
     * @param cst Cost of the pizza
     * @param prof Profit pizzeria make on this pizza
    */
    void AddPizza(std::string nam, int cst, int prof);

    /**
     * Removes drink from menu
     * 
     * @param id ID of the drink that should be removed
    */
    void RemoveDrink(int id);
    /**
     * Removes pizza from menu
     * 
     * @param id ID of the pizza that should be removed
    */
    void RemovePizza(int id);

    /**
     * @param id Id of the drink
     * @return Drink based on inputed ID
    */
    Drink* GetDrink(int id);
    /**
     * @param id Id of the pizza
     * @return Pizza based on inputed ID
    */
    Pizza* GetPizza(int id);

    /**
     * Checks if the drink exists
     * @param id ID of the seeked drink
     * \retval TRUE if exists
     * \retval FALSE if do not exists
    */
    bool DrinkExist(int id);
    /**
     * Checks if the drink exists
     * @param id ID of the seeked drink
     * \retval TRUE if exists
     * \retval FALSE if do not exists
    */
    bool PizzaExist(int id);
    /**
     * Checks if the drink exists
     * @param nam Name of the seeked drink
     * \retval TRUE if exists
     * \retval FALSE if do not exists
    */
    bool SeekDrinkName(std::string nam);
    /**
     * Checks if the pizza exists
     * @param nam Name of the seeked pizza
     * \retval TRUE if exists
     * \retval FALSE if do not exists
    */
    bool SeekPizzaName(std::string nam);
    /**
     * @return Total drinks count
    */
    int GetDrinksCount();
    /**
     * @return Total pizza count
    */
    int GetPizzasCount();
    /**
     * @param id ID of the seeked drink
     * @return Index (order) of this speciffic drink in the menu
    */
    int GetDrinkIndex(int id);
    /**
     * @param id ID of the seeked pizza
     * @return Index (order) of this speciffic pizza in the menu
    */
    int GetPizzaIndex(int id);

    /**
     * @brief Prints the whole menu
     * 
     * Prints the whole menu - every pizza thats in the menu,
     * every drink thats in the menu and their ID and name.
    */
    void PrintWholeMenu();
    /**
     * @brief Starts the drink deletion spree
     * 
     * Deletion process works until theres '-1' on the input.
    */
    void DeletionDrinks();
    /**
     * @brief Starts the pizza deletion spree
     * Deletion process works until theres '-1' on the input.
    */
    void DeletionPizzas();
};