#include <string>
#include <iostream>

#include "Drink.h"

int Drink::static_drinkID = 0;

Drink::Drink(std::string nam, int cst, int prof){
    this->drink_name = nam;
    this->cost = cst;
    this->profit = prof;
    SetDrinkID(static_drinkID);

    static_drinkID++;
}
Drink::~Drink(){
}



void Drink::SetDrinkID(int id){
    this->drink_ID = id;
}



std::string Drink::GetDrinkName(){
    return this->drink_name;
}
int Drink::GetDrinkPrice(){
    return this->cost;
}
int Drink::GetDrinkProfit(){
    return this->profit;
}
int Drink::GetDrinkID(){
    return this->drink_ID;
}
int Drink::GetStaticID(){
    return static_drinkID;
}