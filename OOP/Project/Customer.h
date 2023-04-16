#pragma once
#include <string>
#include <iostream>

#include "Order.h"

#define MAX_ORD 10  //Max orders per customer


class Customer{
private:
    std::string name;
    std::string address;
    int customer_ID;

    Order* orders[MAX_ORD];
    int orders_count;

    static int customer_counter;
public:
    static int overall_orders_count;
    Customer(std::string nam, std::string addrs);
    ~Customer();

    int GetCustID();
    std::string GetCustAddress();
    std::string GetCustName();
    int GetOrdersCount();
    void CreateOrder();
    Order* GetOrder(int index);


};