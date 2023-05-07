#pragma once
#include <string>
#include <iostream>

class AbstractEmployee{
    protected:
        std::string name;
    public:
    /**
     * @brief Abstract class constructor
    */
        virtual ~AbstractEmployee(){}
    
    /**
     * @brief Abstract class destructor
    */
        virtual void EmployeeInfo()=0;
};