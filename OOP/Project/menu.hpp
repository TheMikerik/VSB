#include "pizzas.hpp"

class Menu{
    private:
        int menu_date;
        static int menu_ID;
        Pizzas* pizzas_in_menu;
    public:
        Menu(int date, Pizzas* pizzas){
            this->menu_date=date;
            this->pizzas_in_menu=pizzas;

            menu_ID++;
        }

        int GetMenuDate(){
            return this->menu_date;
        };
        Pizzas* GetPizzasInMenu(){
            return pizzas_in_menu;
        };

        static int GetMenuID();
};

int Menu::menu_ID = 0;

int Menu::GetMenuID(){
    return menu_ID;
};