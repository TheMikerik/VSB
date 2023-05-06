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

    int employee_count;
    int delivery_count;
    int cook_count;
    int customer_count;
    int ids_count;
    int total_orders;
    
    Customer* customers[CUST];
    Employee* employees[E];
    Delivery* deliveries[D];
    Cook* cooks[C];
public:
    Menu menu;

    /**
     * @brief class constructor
     * @param nam Name of the pizzeria
    */
    Pizzeria(std::string nam);
    /**
     * @brief class constructor
     * @param nam Name of the pizzeria
     * @param tel Telephone number of the pizzeria
    */
    Pizzeria(std::string nam, int tel);
    /**
     * @brief Pizzeria class constructor
     * @param nam Name of the pizzeria
     * @param web Website of the pizzeria
    */
    Pizzeria(std::string nam, std::string web);
    /**
     * @brief class constructor
     * @param nam Name of the pizzeria
     * @param tel Telephone number of the pizzeria
     * @param web Website of the pizzeria
    */
    Pizzeria(std::string nam, int tel, std::string web);

    /**
     * @return Pizzeria's name
    */
    std::string GetPizzeriaName();
    /**
     * @return Pizzeria's telephone
    */
    int GetPizzeriaTel();
    /**
     * @return Pizzeria's website
    */
    std::string GetPizzeriaWeb();
    /**
     * @return Pizzeria's employees count
    */
    int GetEmployeesCount();
    /**
     * @param empl_id ID of the employee we wanna seek
     * @return Employee with the exact ID as in input
    */
    Employee* GetEmployee(int empl_id);
    /**
     * @param empl_id ID of the cook we wanna seek
     * @return Cook with the exact ID as in input
    */
    Cook* GetCook(int empl_id);
    /**
     * @param empl_id ID of the delivery we wanna seek
     * @return Delivery with the exact ID as in input
    */
    Delivery* GetDelivery(int empl_id);
    /**
     * @param id ID of the customer we wanna seek
     * @return ustomer with the exact ID as in input
    */
    Customer* GetCustomer(int id);
    /**
     * @param empl_id ID of the employee we wanna seek
     * @return Index in array of the employees of this employee
    */
    int GetEmployeeIndex(int empl_id);
    /**
     * @param empl_id ID of the delivery we wanna seek
     * @return Index in array of the deliveries of this delivery
    */
    int GetDeliveryIndex(int empl_id);
    /**
     * @param empl_id ID of the cook we wanna seek
     * @return Index in array of the deliveries of this cook
    */
    int GetCookIndex(int empl_id);

    /**
     * @brief Create new order for customer with this ID
     * 
     * It finds the customer with this ID and creates new order for him
     * Then there will be posibilitty to add whatever pizza and drink
     * from menu. Lastly after his order was created, it will be printed
     * as an final overview.
     * 
     * @param cust_id ID of the customer that will have this order
    */
    void OrderForCustomer(int cust_id);
    /**
     * @brief Adds new customer to the pizzeria database
     * @param nam New customer's name
     * @param addrs New customer's adress
    */
    void AddCustomer(std::string nam, std::string addrs);
    /**
     * @brief Adds new emplyee as delivery to the pizzeria database
     * @param nam New employee's name
     * @param cook Can cook?
     * @param drive Can drive?
    */
    void AddAsDelivery(std::string nam, bool cook, bool drive);
    /**
     * @brief Adds new employee as cook to the pizzeria database
     * @param nam New employee's name
     * @param cook Can cook?
     * @param drive Can drive?
    */
    void AddAsCook(std::string nam, bool cook, bool drive);
    /**
     * @brief Adds new employee to the pizzeria database
     * @param nam New employee's name
     * @param cook Can cook?
     * @param drive Can drive?
    */
    void AddEmployee(std::string nam, bool cook, bool drive);
    /**
     * @brief Prints info about pizzeria
     * 
     * Detailed info about pizzeria. It will print for exmaple
     * telephone number, website adress, all current employees,
     * customers ect.
    */
    void IntroducePizzeria();
    /**
     * @brief Prints all employees
     * 
     * Print every employee of this pizzeria.
     * It prints their ID and name.
    */
    void PrintEmployees();
    /**
     * @brief Prints all deliveries
     * 
     * Print every delivery of this pizzeria.
     * It prints their ID and name.
    */
    void PrintDelivery();
    /**
     * @brief Prints all cooks
     * 
     * Print every cook of this pizzeria.
     * It prints their ID and name.
    */
    void PrintCook();
    /**
     * @brief Prints all customers
     * 
     * Print every customer of this pizzeria.
     * It prints their ID and name.
    */
    void PrintCustomers();
    /**
     * @brief Shifts order in pizzeria's employee array
     * @param empl_id ID of the employee, that should be replaced
    */
    void ShiftOrderEmplo(int empl_id);
    /**
     * @brief Shifts order in pizzeria's cook array
     * @param empl_id ID of the cook, that should be replaced
    */
    void ShiftOrderCook(int empl_id);
    /**
     * @brief Shifts order in pizzeria's delivery array
     * @param empl_id ID of the delivery, that should be replaced
    */
    void ShiftOrderDeliv(int empl_id);
    /**
     * @brief Deletion of exact employee
     * @param empl_id ID of the employee that should be deleted
    */
    void DeleteEmployee(int empl_id);
    /**
     * @brief Employee deletion init with header
    */
    void Deletion();
    /**
     * @brief Programm stopping method
     * 
     * Totally useless, just so the program can be stopped
     * and all functionalities can be overviewed.
    */
    void StopProgram();
    /**
     * @brief Makes 18 lines of void
     * 
     * Totally useless, just so this program is not that 
     * 
    */
    void MakeSpace();
    /**
     * @brief Checks if seeked employee exists
     * 
     * @param ID ID of the employee
     * \retval TRUE if employee exists
     * \retval FALSE if employee does not exist
    */
    bool EmplExist(int ID);
    /**
     * @brief Tests of the virtual methods
    */
    void TestVirtual();
};