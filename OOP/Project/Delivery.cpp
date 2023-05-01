#include "Delivery.h"

Delivery::Delivery(std::string nam, bool cook, bool drive):Employee(nam, cook, drive){
    gas_money=0;
    orders_delivered=0;

    this->position = "delivery";
}
Delivery::~Delivery(){
}


int Delivery::GetGasMoney(){
    return this->gas_money;
}
int Delivery::GetOrdersDelivered(){
    return this->orders_delivered;
}


void Delivery::EmployeeInfo(){
    std::cout << "This employee's name is " << this->name << " and his position is " << this->position << "." << std::endl;
    std::cout << "This employee delivered " << this->orders_delivered << " orders and spent " << this->gas_money << " $ on gas this month" << std::endl;
}


void Delivery::CalculateGasMoney(){
    float tmp_gas_price = 0;

    tmp_gas_price = this->orders_delivered * 30;

    this->gas_money = tmp_gas_price;
}