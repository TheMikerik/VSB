#pragma once
#include <string>
#include <iostream>
#include "Employee.h"
#include "Delivery.h"
#include "Cook.h"

class Pizzeria{
private:
    std::string name;
    int telephone;
    std::string website;

    bool is_open;
    float income;
    float outcome;
    float profit;

    Employee* employees[10];
    Delivery* deliveries[4];
    Cook* cooks[6];
public:
    Pizzeria(std::string nam);
    Pizzeria(std::string nam, int tel);
    Pizzeria(std::string nam, std::string web);
    Pizzeria(std::string nam, int tel, std::string web);



    std::string GetPizzeriaName();
    int GetPizzeriaTel();
    std::string GetPizzeriaWeb();
    bool IsPizzeriaOpen();
    float GetPizzeriaIncome();
    float GetPizzeriaOutcome();
    float GetPizzeriaProfit();
    int GetEmployeesCount();


    void CloseOpenPizzeria();
    void AddEmployee(std::string nam, bool cook, bool drive);
    void IntroducePizzeria();
    /*
    void CalculateIncome();
    void CalculateOutcome();
    void CalculateProfits();
    */
};