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
    /*
    if (pizzas_in_order < MAX_P){
        ordered_pizzas[pizzas_in_order] = this->menu->GetPizza(ID);
        this->pizzas_in_order++;
        std::cout << menu->GetPizza(ID)->GetPizzaName() << " was added" << std::endl;
    }
    else {
        std::cout << "     You cannot order more pizzas" << std::endl;
    }*/
}
void Order::AddDrink(Drink* drink){
    ordered_drinks[drinks_in_order] = drink;
    std::cout << ordered_drinks[drinks_in_order]->GetDrinkName() << " was added" << std::endl;
    this->drinks_in_order++;
    /*
    if (drinks_in_order < MAX_D){
        ordered_drinks[drinks_in_order] = this->menu->GetDrink(ID);
        this->drinks_in_order++;
        std::cout << menu->GetDrink(ID)->GetDrinkName() << " was added" << std::endl;
    }
    else {
        std::cout << "     You cannot order more drinks" << std::endl;
    }*/
}
int Order::GetOrderID(){
    return this->order_ID;
}