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
Employee* Pizzeria::GetEmployee(int empl_id){
    for (int i=0; i<this->employee_count; i++){
        if ( employees[i]->GetID() == empl_id ){
            return employees[i];
        }
    }
    std::cout << "     This employee was already deleted." << std::endl;
    return nullptr;
}
Cook* Pizzeria::GetCook(int empl_id){
    for (int i=0; i<this->cook_count; i++){
        if ( cooks[i]->GetID() == empl_id ){
            return cooks[i];
        }
    }
    std::cout << "     This employee was already deleted." << std::endl;
    return nullptr;
}
Delivery* Pizzeria::GetDelivery(int empl_id){
    for (int i=0; i<this->delivery_count; i++){
        if ( deliveries[i]->GetID() == empl_id ){
            return deliveries[i];
        }
    }
    std::cout << "     This employee was already deleted." << std::endl;
    return nullptr;
}

int Pizzeria::GetEmployeeIndex(int empl_id){
    for (int i=0; i<this->employee_count; i++){
        if ( employees[i]->GetID() == empl_id ){
            return i;
        }
    }
    std::cout << "This employee was not found" << std::endl;
    return -1;
}
int Pizzeria::GetDeliveryIndex(int empl_id){
    for (int i=0; i<this->delivery_count; i++){
        if ( deliveries[i]->GetID() == empl_id ){
            return i;
        }
    }
    std::cout << "This employee was not found" << std::endl;
    return -1;
}
int Pizzeria::GetCookIndex(int empl_id){
    for (int i=0; i<this->cook_count; i++){
        if ( cooks[i]->GetID() == empl_id ){
            return i;
        }
    }
    std::cout << "This employee was not found" << std::endl;
    return -1;
}


void Pizzeria::CloseOpenPizzeria(){
    is_open = !is_open;
}

void Pizzeria::AddAsDelivery(std::string nam, bool cook, bool drive)
{
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
    std::cout << "Lets print all employees" << std::endl;
    for (int i=0; i < this->employee_count; i++){
        std::cout << "     Worker with ID: " << employees[i]->GetID() <<
        " has name: " << employees[i]->GetName() << std::endl;
    }
}
void Pizzeria::PrintDelivery(){
    std::cout << "\nThose guys working in delivery for us:" << std::endl;
    for (int i=0; i < delivery_count; i++){
        std::cout << "     Delivery worker with ID: " << deliveries[i]->GetID() <<
        " has name: " << deliveries[i]->GetName() << std::endl;
    }
}
void Pizzeria::PrintCook(){
    std::cout << "\nThose guys working as cooks for us:" << std::endl;
    for (int i=0; i < cook_count; i++){
        std::cout << "     Cook worker with ID: " << cooks[i]->GetID() <<
        " has name: " << cooks[i]->GetName() << std::endl;
    }
}
void Pizzeria::ShiftOrderEmplo(int empl_id){
    int i = this->GetEmployeeIndex(empl_id);

    while ( i<this->employee_count ){
        employees[i] = employees[i+1];
        i++;
    }
}
void Pizzeria::ShiftOrderCook(int empl_id){
    //this->ShiftOrderEmplo(empl_id);

    int i = this->GetCookIndex(empl_id);   
    this->GetCook(empl_id)->~Cook();
    cooks[i] = nullptr;

    while ( i<this->cook_count ){
        cooks[i] = cooks[i+1];
        i++;
    }

    this->ShiftOrderEmplo(empl_id);
    this->cook_count--;
}
void Pizzeria::ShiftOrderDeliv(int empl_id){
    //this->ShiftOrderEmplo(empl_id);

    int i = this->GetDeliveryIndex(empl_id);   
    this->GetDelivery(empl_id)->~Delivery();
    deliveries[i] = nullptr;

    while ( i<this->delivery_count ){
        deliveries[i] = deliveries[i+1];
        i++;
    }

    this->ShiftOrderEmplo(empl_id);
    this->delivery_count--;
}
void Pizzeria::DeleteEmployee(int empl_id){
    if ( employee_count < 1){
        std::cout << "     You have deleted all workers" << std::endl;
        return;
    }
    else if ( empl_id > this->ids_count ){
        std::cout << "     Employee with ID " << empl_id << " have never existed" << std::endl;
    }
    else if ( this->GetEmployee(empl_id) == nullptr ){
        return;
    }
    else if ( empl_id < ids_count){
        if (this->GetEmployee(empl_id)->CanCook()){
            this->ShiftOrderCook(empl_id);
        }
        else if (this->GetEmployee(empl_id)->CanDrive()){
            this->ShiftOrderDeliv(empl_id);
        }
     // this->ShiftOrderEmplo(empl_id);

        this->employee_count--;

        std::cout << "     Employee with ID " << empl_id << " have been deleted" << std::endl;
    }
}
void Pizzeria::Deletion(){
    int input;
    std::cout << "\nLets delete some workers\nType ID of the worker that you wanna delete:     (type '-1' to stop)" << std::endl;
    std::cin >> input;
    while ( input != -1){
        this->DeleteEmployee(input);
        std::cin >> input;
    }
}