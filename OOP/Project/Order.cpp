#include <string>
#include <iostream>

#include "Order.h"

int Order::static_order_ID = 0;

Order::Order(){
    this->order_ID = static_order_ID;
    this->pizzas_in_order = 0;
    this->drinks_in_order = 0;

    static_order_ID++;
}
Order::~Order(){
}

void Order::AddPizza(Pizza* pizza){
    ordered_pizzas[pizzas_in_order] = pizza;
    std::cout << ordered_pizzas[pizzas_in_order]->GetPizzaName() << " was added" << std::endl;
    this->pizzas_in_order++;
}
void Order::AddDrink(Drink* drink){
    ordered_drinks[drinks_in_order] = drink;
    std::cout << ordered_drinks[drinks_in_order]->GetDrinkName() << " was added" << std::endl;
    this->drinks_in_order++;
}
int Order::GetPizzasInOrder(){
    return this->pizzas_in_order;
}
int Order::GetDrinksInOrder(){
    return this->drinks_in_order;
}
Pizza* Order::GetPizza(int i){
    return this->ordered_pizzas[i];
}
Drink* Order::GetDrink(int i){
    return this->ordered_drinks[i];
}

int Order::GetOrderID(){
    return this->order_ID;
}