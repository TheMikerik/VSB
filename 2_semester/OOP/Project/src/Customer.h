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
    /**
     * @param nam Name of the customer
     * @param addrs Adress of the customer
     * @brief Customer class constructor
    */
    Customer(std::string nam, std::string addrs);
    /**
     * @brief Customer class destructor
    */
    ~Customer();


    /**
     * @return Customer's ID
    */
    int GetCustID();
    /**
     * @return Customer's adress
    */
    std::string GetCustAddress();
    /**
     * @return Customer's name
    */
    std::string GetCustName();
    /**
     * @return Customer's orders count
    */
    int GetOrdersCount();
    /**
     * @brief Creation of new order
    */
    void CreateOrder();
    /**
     * @param index ID of the seeked order
     * @return Order with selected ID
    */
    Order* GetOrder(int index);


};