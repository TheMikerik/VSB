#include <string>
#include <iostream>

#include "Customer.h"

int Customer::customer_counter = 0;
int Customer::overall_orders_count = 0;

Customer::Customer(std::string nam, std::string addrs){
    this->name = nam;
    this->address = addrs;
    this->customer_ID = customer_counter;
    orders_count = 0;

    customer_counter++;
}

Customer::~Customer(){
}

int Customer::GetCustID(){
    return this->customer_ID;
}
std::string Customer::GetCustAddress(){
    return this->address;
}
std::string Customer::GetCustName(){
    return this->name;
}
int Customer::GetOrdersCount(){
    return this->orders_count;
}
void Customer::CreateOrder(){
    orders[this->orders_count] = new Order();

    this->orders_count++;
    overall_orders_count++;
}

Order* Customer::GetOrder(int index){
    return this->orders[index];
}