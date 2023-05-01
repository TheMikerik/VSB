#pragma once
#include "Employee.h"

class Delivery : public Employee{
private:
    int gas_money;
    int orders_delivered;
public:
    Delivery(std::string nam, bool cook, bool drive);
    ~Delivery();

    int GetGasMoney();
    int GetOrdersDelivered();

    virtual void EmployeeInfo();

    void CalculateGasMoney();
};