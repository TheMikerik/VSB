#include <string>
#include <iostream>

#include "Order.h"

int Order::static_order_ID = 0;

Order::Order(Menu* from_menu){
    this->order_ID = static_order_ID;
    pizzas_in_order = 0;
    drinks_in_order = 0;

    menu = from_menu;

    static_order_ID++;
}

void Order::AddPizza(int ID){
    if (pizzas_in_order < MAX_P){
        ordered_pizzas[pizzas_in_order] = this->menu->GetPizza(ID);
        this->pizzas_in_order++;
        std::cout << menu->GetPizza(ID)->GetPizzaName() << " was added" << std::endl;
    }
    else {
        std::cout << "     You cannot order more pizzas" << std::endl;
    }
}
void Order::AddDrink(int ID){
    if (drinks_in_order < MAX_D){
        ordered_drinks[drinks_in_order] = this->menu->GetDrink(ID);
        this->drinks_in_order++;
        std::cout << menu->GetDrink(ID)->GetDrinkName() << " was added" << std::endl;
    }
    else {
        std::cout << "     You cannot order more drinks" << std::endl;
    }
}
int Order::GetOrderID(){
    return this->order_ID;
}