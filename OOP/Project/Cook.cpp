#include <string>

#include "Cook.h"

Cook::Cook(std::string nam, bool cook, bool drive):Employee(nam, cook, drive){
    this->pizzas_made = 0;

    this->position = "cook";
}
Cook::~Cook(){
}

void Cook::EmployeeInfo(){
    std::cout << "This employee's name is " << this->name << " and his position is " << this->position << "." << std::endl;
    std::cout << "This employee made " << this->pizzas_made << " pizzas this month" << std::endl;
}

int Cook::GetPizzasMade(){
    return this->pizzas_made;
}
