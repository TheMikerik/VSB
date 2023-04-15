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
    int id = Employee::GetEmplCount();
    if ( cook || drive ){
        employees[id] = new Employee(nam, cook, drive);
        


        std::cout << "     Employee " << nam << " has been added." << std::endl;
    }
    else {
        std::cout << "     Employee " << nam << " cannot be added. (useless)"<< std::endl;
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