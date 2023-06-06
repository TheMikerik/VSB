#pragma once
#include "account.hpp"

class PartnerAccount : public Account
{
private:
    Client* partner;

public:
    PartnerAccount(int n, Client *c, Client *p) : Account(n, c){
        this->partner = p;
    }
    PartnerAccount(int n, Client *c, Client *p, double ir) : Account(n, c, ir){
        this->partner = p;
    }

    virtual bool CanWithdraw(double a){
            if ((Account::balance - a) >= 0){

                return true;
            }
            else{
                return false;
            }
        };
};