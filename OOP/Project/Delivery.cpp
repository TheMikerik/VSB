#include <string>
#include <iostream>

#include "Delivery.h"

int Delivery::empl_delivery_count = 0;

Delivery::Delivery(std::string nam, bool cook, bool drive):Employee(nam, cook, drive){
    gas_money=0;
    orders_delivered=0;

    empl_delivery_count++;
}



std::string Delivery::GetCarID(){
    return this->car_ID;
}

int Delivery::GetGasMoney(){
    return this->gas_money;
}

int Delivery::GetOrdersDelivered(){
    return this->orders_delivered;
}



int Delivery::GetEmplDeliveryCount(){
    return empl_delivery_count;
}



void Delivery::CalculateGasMoney(){
    float tmp_gas_price = 0;

    tmp_gas_price = this->orders_delivered * 30;

    this->gas_money = tmp_gas_price;
}