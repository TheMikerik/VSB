#include <string>
#include <iostream>

#include "Employee.h"

int Employee::empl_count = 0;
int Employee::empl_ID = 0;

Employee::Employee(std::string nam, bool cook, bool drive){
    this->name = nam;
    this->can_cook = cook;
    this->can_drive = drive;

    empl_count++;
    empl_ID++;
}



std::string Employee::GetName(){
    return this->name;
}

int Employee::GetID(){
    return this->empl_ID;
}

int Employee::GetWorkedHours(){
    return this->hours_worked;
}

int Employee::GetWorkedYears(){
    return this->years_worked;
}

int Employee::GetSalary(){
    return this->salary;
}



void Employee::CalculateSalary(){
    float tmp_salary = this->salary;

    tmp_salary *= 1 + (2*(this->years_worked / 100));

    this->salary = (int)tmp_salary;
}

bool Employee::CanChangePosition(){
    if (this->can_cook && this->can_drive){
        return 1;
    }
    else{
        return 0;
    }
}



int Employee::GetEmplCount(){
    return empl_count;
}