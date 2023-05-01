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
    Employee(std::string nam, bool cook, bool drive);
    ~Employee();

    void SetID(int id);
    
    std::string GetName();
    int GetID();
    int GetWorkedHours();
    int GetWorkedYears();
    int GetSalary();
    bool CanCook();
    bool CanDrive();

    virtual void EmployeeInfo();

    void CalculateSalary();
    bool CanChangePosition();
};