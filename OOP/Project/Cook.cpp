#include <string>
#include <iostream>

#include "Cook.h"
#include "Employee.h"

int Cook::empl_cooks_count = 0;

Cook::Cook(std::string nam, bool cook, bool drive):Employee(nam, cook, drive){
    this->pizzas_made = 0;

    empl_cooks_count++;
}



int Cook::GetPizzasMade(){
    return this->pizzas_made;
}



int Cook::GetEmplCooksCount(){
    return empl_cooks_count;
}