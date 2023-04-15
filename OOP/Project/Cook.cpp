#include <string>
#include <iostream>

#include "Cook.h"
#include "Employee.h"

Cook::Cook(std::string nam, bool cook, bool drive):Employee(nam, cook, drive){
    this->pizzas_made = 0;
}

int Cook::GetPizzasMade(){
    return this->pizzas_made;
}