#pragma once
#include <string>
#include <iostream>
#include "Employee.h"

class Cook : public Employee{
private:
    int pizzas_made;
    
public:
    static int empl_cooks_count;

    Cook(std::string nam, bool cook, bool drive);

    int GetPizzasMade();

    static int GetEmplCooksCount();
};  