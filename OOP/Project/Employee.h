#pragma once
#include <string>
#include <iostream>

class Employee{
private:
    std::string name;
    bool can_cook;
    bool can_drive;
    int empl_ID;

    int hours_worked;
    int years_worked;
    int salary;
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

    void CalculateSalary();
    bool CanChangePosition();
};