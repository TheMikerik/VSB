#pragma once
#include <string>
#include <iostream>

class AbstractEmployee{
    protected:
        std::string name;
    public:
        virtual ~AbstractEmployee(){}
        virtual void EmployeeInfo()=0;
};