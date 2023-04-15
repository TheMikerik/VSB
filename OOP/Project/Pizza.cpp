#include <string>
#include <iostream>

#include "Pizza.h"

int Pizza::static_pizzaID = 0;

Pizza::Pizza(std::string nam, int cst, int prof){
    this->pizza_name = nam;
    this->cost = cst;
    this->profit = prof;
    SetPizzaID(static_pizzaID);

    static_pizzaID++;
}
Pizza::~Pizza(){
}



void Pizza::SetPizzaID(int id){
    this->pizza_ID = id;
}



std::string Pizza::GetPizzaName(){
    return this->pizza_name;
}
int Pizza::GetPizzaPrice(){
    return this->cost;
}
int Pizza::GetPizzaProfit(){
    return this->profit;
}
int Pizza::GetPizzaID(){
    return this->pizza_ID;
}
int Pizza::GetStaticID(){
    return static_pizzaID;
}