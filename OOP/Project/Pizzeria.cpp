#include <string>
#include <iostream>

#include "Pizzeria.h"

Pizzeria::Pizzeria(std::string nam){
    this->name = nam;

    this->employee_count = 0;
    this->delivery_count = 0;
    this->cook_count = 0;
    this->customer_count = 0;
    this->ids_count = 0;
    this->total_orders = 0;
}
Pizzeria::Pizzeria(std::string nam, int tel){
    this->name = nam;
    this->telephone = tel;

    this->employee_count = 0;
    this->delivery_count = 0;
    this->cook_count = 0;
    this->customer_count = 0;
    this->ids_count = 0;
    this->total_orders = 0;
}
Pizzeria::Pizzeria(std::string nam, std::string web){
    this->name = nam;
    this->website = web;

    this->employee_count = 0;
    this->delivery_count = 0;
    this->cook_count = 0;
    this->customer_count = 0;
    this->ids_count = 0;
    this->total_orders = 0;
}
Pizzeria::Pizzeria(std::string nam, int tel, std::string web){
    this->name = nam;
    this->telephone = tel;
    this->website = web;

    this->employee_count = 0;
    this->delivery_count = 0;
    this->cook_count = 0;
    this->customer_count = 0;
    this->ids_count = 0;
    this->total_orders = 0;
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
Customer* Pizzeria::GetCustomer(int id){
    for (int i=0; i<this->customer_count; i++){
        if ( customers[i]->GetCustID() == id ){
            return customers[i];
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

void Pizzeria::OrderForCustomer(int cust_id){

    std::cout << "Creating order for customer with ID " << this->GetCustomer(cust_id)->GetCustID() << std::endl;
    int input = 0;
    int index;
    this->GetCustomer(cust_id)->CreateOrder();

    this->menu.PrintWholeMenu();

    std::cout << "Type pizzas ID that you want to put into order ('-1' for exit)" << std::endl;
    std::cout <<"     ";
    std::cin >> input;
    while (input != -1){
        index = ((this->GetCustomer(cust_id)->GetOrdersCount()) - 1 );
        std::cout <<"     ";
        this->GetCustomer(cust_id)->GetOrder(index)->AddPizza(this->menu.GetPizza(input));
        std::cout <<"     ";
        std::cin >> input;     
    }
    input = 0;
    std::cout << "Type drinks ID that you want to put into order ('-1' for exit)" << std::endl;
    std::cout <<"     ";
    std::cin >> input;
    while (input != -1){
        std::cout <<"     ";
        this->GetCustomer(cust_id)->GetOrder(index)->AddDrink(this->menu.GetDrink(input));
        std::cout <<"     ";
        std::cin >> input;
    }
    this->MakeSpace();
}
void Pizzeria::AddCustomer(std::string nam, std::string addrs){
    int tmp_customer_index = this->customer_count;
    customers[tmp_customer_index] = new Customer(nam, addrs);
    std::cout << "     Customer " << nam << " has been added. " << std::endl;

    this->customer_count++;
}
void Pizzeria::AddAsDelivery(std::string nam, bool cook, bool drive)
{
    if ( this->delivery_count > D || ( this->cook_count + this->delivery_count ) >= E){
        std::cout << " (x) Cannot add more employees as delivery" << std::endl;
    }
    else{
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
}
void Pizzeria::AddAsCook(std::string nam, bool cook, bool drive){
    if ( this->cook_count > C || ( this->cook_count + this->delivery_count ) >= E){
        std::cout << " (x) Cannot add more employees as cook" << std::endl;
    }
    else{
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
        std::cout << " (x) Employee " << nam << " cannot cook or drive - not added."<< std::endl;
    }
}
void Pizzeria::IntroducePizzeria(){
    std::cout << "\nPizzeria info checker:" << std::endl;
    std::cout << "     Its name is: " << this->GetPizzeriaName() <<
    "\n     Its telephone number is: " << this->GetPizzeriaTel() <<
    "\n     Its webiste is: " << this->GetPizzeriaWeb() <<
    "\n     It has currently " << this->GetEmployeesCount() <<" employees" <<
    "\n                      " << this->delivery_count <<" working as delivery" <<
    "\n                      " << this->cook_count <<" working as cooks" <<
    "\n     It has currently " << this->menu.GetPizzasCount() << " pizzas in menu" <<
    "\n     It has currently " << this->menu.GetDrinksCount() << " drinks in menu" << 
    "\n     It has currently " << this->customer_count << " customers" <<
    "\n     And " << Customer::overall_orders_count << " orders in total\n" << std::endl;
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
void Pizzeria::PrintCustomers(){
    std::cout << "\nThose guys are ours customers:" << std::endl;
    for (int i=0; i < customer_count; i++){
        std::cout << "     Customer with ID: " << customers[i]->GetCustID() <<
        " has name: " << customers[i]->GetCustName() << " and address: " <<
        customers[i]->GetCustAddress() << std::endl;
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
    std::cout <<"     ";
    std::cin >> input;
    while ( input != -1){
        this->DeleteEmployee(input);
        std::cout <<"     ";
        std::cin >> input;
    }
}
void Pizzeria::StopProgram(){
    int input;
    std::cout << "\n-----------------------------";
    std::cout << "\n-------PROGRAM STOPPED-------";
    std::cout << "\n-----------------------------     (type '-1' to run)";
    std::cout <<"     ";
    std::cin >> input;
    while ( input != -1){
        std::cout << "Type '-1' to run program" << std::endl;
        std::cout <<"     ";
        std::cin >> input;
    }
    std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}
void Pizzeria::MakeSpace(){
    std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}