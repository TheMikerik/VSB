#include "menu.hpp"

class Pizzeria{
    private:
        std::string pizzeria_name;
        int pizzeria_telephone;
        bool pizzeria_open;        

        Menu* menu;
        //Customers* customers;
        //Emplyees* employees;

        static int pizzerias_count;
    public:
        Pizzeria(std::string name){
            this->pizzeria_name=name;
            this->pizzeria_telephone = 0;
            this->pizzeria_open = 0;

            pizzerias_count++;
        };

        std::string GetPizzeriaName(){
            return this->pizzeria_name;
        }

        void SetPizzeriaPhone(int number){
            this->pizzeria_telephone=number;
        }
        void OpenPizzeria(){
            this->pizzeria_open = true;
        }
        void ClosePizzeria(){
            this->pizzeria_open = false;
        }

        static int GetPizzeriasCount();
};

int Pizzeria::pizzerias_count = 0;

int Pizzeria::GetPizzeriasCount(){
    return pizzerias_count;
}

