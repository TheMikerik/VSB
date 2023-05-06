#pragma once
#include "Employee.h"

class Delivery : public Employee{
private:
    int gas_money;
    int orders_delivered;
public:
    /**
     * @brief Delivery class constructor
    */
    Delivery(std::string nam, bool cook, bool drive);
    /**
     * @brief Delivery class destructor
    */
    ~Delivery();

    /**
     * @return Money spent on gas
    */
    int GetGasMoney();
    /**
     * @return Total orders delivered
    */
    int GetOrdersDelivered();
    /**
     * @brief Bacis info about this delivery guy
     * 
     * Prints name, position, total orders delivered and money spent on gas
    */
    virtual void EmployeeInfo();
    /**
     * @brief Calculate money spent on gas
     * 
     * Pizzeria gives 30czk for every order their employee delivere.
     * So this is just (orders_delivered) * 30.
    */
    void CalculateGasMoney();
};