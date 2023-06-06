#include <iostream>
#include <string>
#include "bank.hpp"


int main(){
    //Create bank with 6 clients and 4 accounts
    Bank testBank(6, 4);
    //Create 4 clients
    //Client* MR;
    testBank.CreateClient(0, "Michal Rucka");
    testBank.CreateClient(1, "Marek Zacek");
    testBank.CreateClient(2, "Rostislav Vrana");
    testBank.CreateClient(3, "Vilem Zamboch");
    //Create 2 partners
    testBank.CreateClient(4, "Pani Vranova");
    testBank.CreateClient(5, "Pani Zambochova");

    //Create 4 different types of bank accounts
    testBank.CreateAccount(0, testBank.GetClient(0));
    testBank.CreateAccount(1, testBank.GetClient(1), 2);
    testBank.CreateAccount(2, testBank.GetClient(2), testBank.GetClient(4));
    testBank.CreateAccount(3, testBank.GetClient(3), testBank.GetClient(5), 3);

    cout << testBank.GetClient(3)->GetName() << endl;
    cout << testBank.GetClient(4)->GetName() << endl;
    cout << testBank.GetClient(0)->GetName() << endl;

    cout << testBank.GetAccount(0)->GetOwner()->GetName() << endl;
    cout << testBank.GetAccount(1)->GetOwner()->GetName() << endl;
    cout << testBank.GetAccount(2)->GetOwner()->GetName() << endl;
    cout << testBank.GetAccount(3)->GetOwner()->GetName() << endl;

    //cout << testBank.GetAccount(0)->GetPartner()->GetName() << endl;
    //cout << testBank.GetAccount(1)->GetPartner()->GetName() << endl;
    cout << testBank.GetAccount(2)->GetPartner()->GetName() << endl;
    cout << testBank.GetAccount(3)->GetPartner()->GetName() << endl;


    return 0;
}
