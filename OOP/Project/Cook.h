#pragma once
#include <string>
#include <iostream>
#include "Employee.h"

class Cook : public Employee{
private:
    int pizzas_made;
public:
    Cook(std::string nam, bool cook, bool drive);
    ~Cook();

    int GetPizzasMade();
};  