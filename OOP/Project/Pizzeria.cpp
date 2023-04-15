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
    return this->employee_count;
}



void Pizzeria::CloseOpenPizzeria(){
    is_open = !is_open;
}
void Pizzeria::AddAsDelivery(std::string nam, bool cook, bool drive){
    int empl_index = this->employee_count;
    int deliv_index = this->delivery_count;
    deliveries[deliv_index] = new Delivery(nam, cook, drive);
    employees[empl_index] = deliveries[deliv_index];
    std::cout << "     Employee " << nam << " has been added. (delivery)" << std::endl;

    this->employees[empl_index]->SetID(ids_count);
    
    this->delivery_count++;
    this->employee_count++;
    this->ids_count++;
}
void Pizzeria::AddAsCook(std::string nam, bool cook, bool drive){
    int empl_index = this->employee_count;
    int cook_index = this->cook_count;
    cooks[cook_index] = new Cook(nam, cook, drive);
    employees[empl_index] = cooks[cook_index];
    std::cout << "     Employee " << nam << " has been added. (cook)" << std::endl;

    this->employees[empl_index]->SetID(ids_count);

    this->cook_count++;
    this->employee_count++;
    this->ids_count++;
}



void Pizzeria::AddEmployee(std::string nam, bool cook, bool drive){
    if ( cook || drive ){
        if (cook && drive){
            AddAsCook(nam, cook, drive);
        }
        else if (cook){
            AddAsCook(nam, cook, drive);
        }
        else if (drive){
            AddAsDelivery(nam, cook, drive);
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
void Pizzeria::PrintEmployees(){
    for (int i=0; i < this->employee_count; i++){
        std::cout << "     Worker with ID: " << employees[i]->GetID() <<
        " has name: " << employees[i]->GetName() << std::endl;
    }
}
void Pizzeria::PrintDelivery(){
    for (int i=0; i < delivery_count; i++){
        std::cout << "     Delivery worker with ID: " << deliveries[i]->GetID() <<
        " has name: " << deliveries[i]->GetName() << std::endl;
    }
}
void Pizzeria::PrintCook(){
    for (int i=0; i < cook_count; i++){
        std::cout << "     Cook worker with ID: " << cooks[i]->GetID() <<
        " has name: " << cooks[i]->GetName() << std::endl;
    }
}