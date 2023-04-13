#pragma once
#include <iostream>


class Pizzas{
    private:
        int pizza_ID;
        std::string pizza_name;

        static int pizza_count;
    public:
        Pizzas(int ID, std::string name){
            this->pizza_ID=ID;
            this->pizza_name=name;
            pizza_count++;
        }
        ~Pizzas(){
            pizza_count--;
        }

        int GetPizzaID(){
            return this->pizza_ID;
        }
        std::string GetPizzaName(){
            return this->pizza_name;
        }

        static int GetPizzasCount();
};

int Pizzas::pizza_count = 0;

int Pizzas::GetPizzasCount(){
    return Pizzas::pizza_count;
}