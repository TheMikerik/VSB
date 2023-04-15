#pragma once
#include <string>
#include <iostream>

class Employee{
private:
    std::string name;
    bool can_cook;
    bool can_drive;

    int hours_worked;
    int years_worked;
    int salary;
public:
    static int empl_count;
    static int empl_ID;

    Employee(std::string nam, bool cook, bool drive);

    std::string GetName();
    static int GetID();
    int GetWorkedHours();
    int GetWorkedYears();
    int GetSalary();

    void CalculateSalary();
    bool CanChangePosition();

    static int GetEmplCount();
};