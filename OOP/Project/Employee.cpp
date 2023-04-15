#include <string>
#include <iostream>

#include "Employee.h"

Employee::Employee(std::string nam, bool cook, bool drive){
    this->name = nam;
    this->can_cook = cook;
    this->can_drive = drive;
}
Employee::~Employee(){
}

void Employee::SetID(int id){
    this->empl_ID = id;
}



std::string Employee::GetName(){
    return this->name;
}
int Employee::GetID(){
    return empl_ID;
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
bool Employee::CanCook(){
    return can_cook;
}
bool Employee::CanDrive(){
    return can_drive;
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