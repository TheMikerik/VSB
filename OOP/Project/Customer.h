#pragma once
#include <string>
#include <iostream>

#include "Order.h"

#define MAX_ORD 10  //Max orders per customer


class Customer{
public:
    virtual void NewOrder()=0;
};

class NewCustomer : public Customer{
private:
    std::string name;
    std::string address;
    int customer_ID;

    Order* orders[MAX_ORD];
    int orders_count;

    static int customer_counter;
public:
    NewCustomer(std::string nam, std::string addrs);
    ~NewCustomer();

    int GetCustID();
    std::string GetCustAddress();
    std::string GetCustName();
    int GetOrdersCount();

    void NewOrder(Menu* menu);
};