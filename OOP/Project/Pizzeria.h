#pragma once
#include <string>
#include <iostream>

//#include "Employee.h"
#include "Delivery.h"
#include "Cook.h"
#include "Customer.h"
#include "Menu.h"

#define E 30    // EMPLOYEES
#define D 15    // DELIVERY
#define C 15    // COOK
#define CUST 15 // CUSTOMERS

class Pizzeria{
private:
    std::string name;
    int telephone;
    std::string website;

    bool is_open=true;
    float income=0;
    float outcome=0;
    float profit=0;
    int employee_count=0;
    int delivery_count=0;
    int cook_count=0;
    int ids_count=0;
    
    Customer* customers[CUST];
    Employee* employees[E];
    Delivery* deliveries[D];
    Cook* cooks[C];
public:
    Pizzeria(std::string nam);
    Pizzeria(std::string nam, int tel);
    Pizzeria(std::string nam, std::string web);
    Pizzeria(std::string nam, int tel, std::string web);

    Menu menu;

    void SetMenu();
    Menu* GetMenu();
    std::string GetPizzeriaName();
    int GetPizzeriaTel();
    std::string GetPizzeriaWeb();
    bool IsPizzeriaOpen();
    float GetPizzeriaIncome();
    float GetPizzeriaOutcome();
    float GetPizzeriaProfit();
    int GetEmployeesCount();
    Employee* GetEmployee(int empl_id);
    Cook* GetCook(int empl_id);
    Delivery* GetDelivery(int empl_id);
    int GetEmployeeIndex(int empl_id);
    int GetDeliveryIndex(int empl_id);
    int GetCookIndex(int empl_id);

    void CloseOpenPizzeria();
    void AddAsDelivery(std::string nam, bool cook, bool drive);
    void AddAsCook(std::string nam, bool cook, bool drive);
    void AddEmployee(std::string nam, bool cook, bool drive);
    void IntroducePizzeria();
    void PrintEmployees();
    void PrintDelivery();
    void PrintCook();
    void ShiftOrderEmplo(int empl_id);
    void ShiftOrderCook(int empl_id);
    void ShiftOrderDeliv(int empl_id);
    void DeleteEmployee(int empl_id);
    void Deletion();
};