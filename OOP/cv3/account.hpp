#include <iostream>
#include <string>
#include "client.hpp"

class Account{
    private:
        int number;
        double balance;
        double interestRate;

        Client *owner;
        Client *partner;
    public:
        Account(int n, Client *c){
            number = n;
            owner = c;
        }
        Account(int n, Client *c, double ir){
            number = n;
            owner = c;
            interestRate = ir;
        }
        Account(int n, Client *c, Client *p){
            number = n;
            owner = c;
            partner = p;
        }
        Account(int n, Client *c, Client *p, double ir){
            number = n;
            owner = c;
            partner = p;
            interestRate = ir;
        }

        int GetNumber(){
            return number;
        };

        double GetBalance(){
            return balance;
        };

        double GetInterestRate(){
            return interestRate;
        };

        Client *GetOwner(){
            return owner;
        };

        Client *GetPartner(){
            return partner;
        };

        bool CanWithdraw(double a){
            if ((balance - a) >= 0){

                return true;
            }
            else{
                return false;
            }
        };

        void Deposit(double a){
            balance += a;
        };

        bool Withdraw(double a){
            if (CanWithdraw(a)){
                balance -= a;
                cout << "Withdraw was successful." << endl;
                return true;
            }
            else{
                cout << "This amount cannot be withdraw" << endl;
                return false;
            }
        };

        void AddInterest(){
            balance *= (interestRate/100);
        };
};