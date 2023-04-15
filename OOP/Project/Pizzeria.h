#pragma once
#include <string>
#include <iostream>
#include "Employee.h"
#include "Delivery.h"
#include "Cook.h"

#define E 15    // EMPLOYEES
#define D 10    // DELIVERY
#define C 10    // COOK

class Pizzeria{
private:
    std::string name;
    int telephone;
    std::string website;

    bool is_open;
    float income;
    float outcome;
    float profit;
    int employee_count=0;
    int delivery_count=0;
    int cook_count=0;
    int ids_count=0;

    Employee* employees[E];
    Delivery* deliveries[D];
    Cook* cooks[C];
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
    void AddAsDelivery(std::string nam, bool cook, bool drive);
    void AddAsCook(std::string nam, bool cook, bool drive);
    void AddEmployee(std::string nam, bool cook, bool drive);
    void IntroducePizzeria();
    void PrintEmployees();
    void PrintDelivery();
    void PrintCook();
    /*
    void CalculateIncome();
    void CalculateOutcome();
    void CalculateProfits();
    */
};