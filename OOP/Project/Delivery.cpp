#include <string>
#include <iostream>

#include "Delivery.h"

Delivery::Delivery(std::string nam, bool cook, bool drive):Employee(nam, cook, drive){
    gas_money=0;
    orders_delivered=0;
}



int Delivery::GetGasMoney(){
    return this->gas_money;
}
int Delivery::GetOrdersDelivered(){
    return this->orders_delivered;
}



void Delivery::CalculateGasMoney(){
    float tmp_gas_price = 0;

    tmp_gas_price = this->orders_delivered * 30;

    this->gas_money = tmp_gas_price;
}