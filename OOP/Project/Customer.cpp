#include <string>
#include <iostream>

#include "Customer.h"

int NewCustomer::customer_counter = 0;

NewCustomer::NewCustomer(std::string nam, std::string addrs){
    this->name = nam;
    this->address = addrs;
    this->customer_ID = customer_counter;
    orders_count = 0;

    customer_counter++;
}

NewCustomer::~NewCustomer(){
}

int NewCustomer::GetCustID(){
    return this->customer_ID;
}
std::string NewCustomer::GetCustAddress(){
    return this->address;
}
std::string NewCustomer::GetCustName(){
    return this->name;
}
int NewCustomer::GetOrdersCount(){
    return this->orders_count;
}

void NewCustomer::NewOrder(Menu* menu){
    this->orders[orders_count] = new Order(menu);
    this->orders_count++;
}