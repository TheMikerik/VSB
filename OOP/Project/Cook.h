#pragma once

#include "Employee.h"

class Cook : public Employee{
private:
    int pizzas_made;
public:
    /**
     * @brief Cook class constructor
    */
    Cook(std::string nam, bool cook, bool drive);
    /**
     * @brief Cook class constructor
    */
    ~Cook();

    /**
     * @brief Bacis info about this cook
     * 
     * Prints name, position and how many pizzas he made
    */
    virtual void EmployeeInfo();

    /**
     * @return Number of pizzas made by this employee
    */
    int GetPizzasMade();
};  