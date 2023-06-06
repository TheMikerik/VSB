#pragma once
#include "client.hpp"

class Account{
    private:
        int number;
        double interestRate;

        Client *owner;
        Client *partner;

        static int accountCount;
    protected:
        double balance;
    public:
        Account(int n, Client *c){
            number = n;
            owner = c;
            interestRate = 0;

            accountCount++;
        }
        Account(int n, Client *c, double ir){
            number = n;
            owner = c;
            interestRate = ir;

            accountCount++;
        }

        static int GetAccountCount();

        ~Account(){
            accountCount--;
        }

        void SetInterestRate(double ir){
            interestRate = ir;
        };

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

        virtual bool CanWithdraw(double a){
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
               // cout << "Withdraw was successful." << endl;
                return true;
            }
            else{
               // cout << "This amount cannot be withdraw" << endl;
                return false;
            }
        };

        void AddInterest(){
            balance *= (interestRate/100);
        };
};

int Account::accountCount = 0;

int Account::GetAccountCount(){
    return Account::accountCount;
}