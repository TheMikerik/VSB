#pragma once

#include "Employee.h"

class Cook : public Employee{
private:
    int pizzas_made;
public:
    Cook(std::string nam, bool cook, bool drive);
    ~Cook();

    virtual void EmployeeInfo();

    int GetPizzasMade();
};  