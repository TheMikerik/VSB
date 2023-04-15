#pragma once
#include <string>
#include <iostream>
#include "Employee.h"

class Delivery : public Employee {
private:
    std::string car_ID;

    int gas_money;
    int orders_delivered;
public:
    static int empl_delivery_count;

    Delivery(std::string nam, bool cook, bool drive);

    std::string GetCarID();
    int GetGasMoney();
    int GetOrdersDelivered();

    void CalculateGasMoney();

    int GetEmplDeliveryCount();
};