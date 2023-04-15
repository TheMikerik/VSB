#include <string>
#include <iostream>

#include "Pizzeria.h"

Pizzeria::Pizzeria(std::string nam){
    this->name = nam;
}
Pizzeria::Pizzeria(std::string nam, int tel){
    this->name = nam;
    this->telephone = tel;
}
Pizzeria::Pizzeria(std::string nam, std::string web){
    this->name = nam;
    this->website = web;
}
Pizzeria::Pizzeria(std::string nam, int tel, std::string web){
    this->name = nam;
    this->telephone = tel;
    this->website = web;
}



std::string Pizzeria::GetPizzeriaName(){
    return this->name;
}
int Pizzeria::GetPizzeriaTel(){
    return this->telephone;
}
std::string Pizzeria::GetPizzeriaWeb(){
    return this->website;
}
bool Pizzeria::IsPizzeriaOpen(){
    return this->is_open;
}
float Pizzeria::GetPizzeriaIncome(){
    return this->income;
}
float Pizzeria::GetPizzeriaOutcome(){
    return this->outcome;
}
float Pizzeria::GetPizzeriaProfit(){
    return this->profit;
}
int Pizzeria::GetEmployeesCount(){
    return Employee::GetEmplCount();
}



void Pizzeria::CloseOpenPizzeria(){
    is_open = !is_open;
}
void Pizzeria::AddEmployee(std::string nam, bool cook, bool drive){
    int emp_index = Employee::GetEmplCount();
    int emp_id = Employee::GetID();

    if ( cook || drive ){
       // employees[emp_index] = new Employee(nam, cook, drive);
        if (cook && drive){
            int deliv_index = Delivery::GetEmplDeliveryCount();
            deliveries[deliv_index] = new Delivery(nam, cook, drive);
            std::cout << "     Employee " << nam << " has been added. (delivery)" << std::endl;
        }
        else if (cook){
            int cook_index = Cook::GetEmplCooksCount();
            cooks[cook_index] = new Cook(nam, cook, drive);
            std::cout << "     Employee " << nam << " has been added. (cook)" << std::endl;
        }
        else if (drive){
            int deliv_index = Delivery::GetEmplDeliveryCount();
            deliveries[deliv_index] = new Delivery(nam, cook, drive);
            std::cout << "     Employee " << nam << " has been added. (delivery)" << std::endl;
        }
    }
    else {
        std::cout << " (x) Employee " << nam << " cannot be added."<< std::endl;
    }
}
void Pizzeria::IntroducePizzeria(){
    std::cout << "\nPizzeria info checker:" << std::endl;
    std::cout << "     Its name is: " << this->GetPizzeriaName() <<
    "\n     Its telephone number is: " << this->GetPizzeriaTel() <<
    "\n     Its webiste is: " << this->GetPizzeriaWeb() <<
    "\n     It has currently " << this->GetEmployeesCount() <<
    " employees\n" << std::endl;
}