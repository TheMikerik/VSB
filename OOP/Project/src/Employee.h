#pragma once

#include "AbstractEmoloyee.h"

class Employee : public AbstractEmployee{
private:
    bool can_cook;
    bool can_drive;
    int empl_ID;

    int hours_worked;
    int years_worked;
    int salary;
protected:
    std::string position;
public:
    /**
     * Employee class constructor
     * @param nam Name of the employee
     * @param cook Can this person cook?
     * @param drive Can this person drive?
    */
    Employee(std::string nam, bool cook, bool drive);
    /**
     * Employee class destructor
    */
    ~Employee();

    /**
     * @brief Sets the id of the employee
     * @param id New ID of the employee
    */
    void SetID(int id);
    
    /**
     * @return Name of the employee
    */
    std::string GetName();
    /**
     * @return ID of the employee
    */
    int GetID();
    /**
     * @return Amount of hours this employee have worked in this month
    */
    int GetWorkedHours();
    /**
     * @return Amount of years this employee have been working for this pizzeria
    */
    int GetWorkedYears();
    /**
     * @return Employee's salary
    */
    int GetSalary();
    /**
     * \retval TRUE if this person can cook
     * \retval FALSE if this persno cannot cook
    */
    bool CanCook();
    /**
     * \retval TRUE if this person can drive
     * \retval FALSE if this persno cannot drive
    */
    bool CanDrive();
    /**
     * @brief Prints basic info about this exact employee
     * 
     * This will print name and current position
    */
    virtual void EmployeeInfo();

    /**
     * @brief Calculates salary
     * 
     * This calculates salary based on years worked in this pizzeria
    */
    void CalculateSalary();
    /**
     * \retval TRUE If the person have abillity to change position
     * \retval FALSE If the person does not have an abilitty to change position
    */
    bool CanChangePosition();
};