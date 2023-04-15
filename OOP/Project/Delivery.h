#pragma once
#include <string>
#include <iostream>
#include "Employee.h"

class Delivery : public Employee {
private:
    int gas_money;
    int orders_delivered;
public:
    Delivery(std::string nam, bool cook, bool drive);

    int GetGasMoney();
    int GetOrdersDelivered();

    void CalculateGasMoney();
};