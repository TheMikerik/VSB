#include "bank.hpp"


int main(){
    //Create bank with 6 clients and 4 accounts
    Bank testBank(6, 4);
    //Create 4 clients
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

    //Print clients
    cout << "Program will print names of the clients" << endl;
    cout << testBank.GetClient(3)->GetName() << endl;
    cout << testBank.GetClient(4)->GetName() << endl;
    cout << testBank.GetClient(0)->GetName() << endl;

    //Print account owners
    cout << "\nProgram will print names of owners of the account" << endl;
    cout << testBank.GetAccount(0)->GetOwner()->GetName() << endl;
    cout << testBank.GetAccount(1)->GetOwner()->GetName() << endl;
    cout << testBank.GetAccount(2)->GetOwner()->GetName() << endl;
    cout << testBank.GetAccount(3)->GetOwner()->GetName() << endl;

    cout << "\nProgram will print names of partners of clints" << endl;
    cout << testBank.GetAccount(2)->GetPartner()->GetName() << endl;
    cout << testBank.GetAccount(3)->GetPartner()->GetName() << endl;

    //Deposit of 100czk
    cout << "\nTo verify if this program works, now lets test some basic operations" << endl;
    cout << "\nLets add 100czk to Michal Rucka's account." << endl;
    cout << "Account owned by: " << testBank.GetClient(0)->GetName() <<
    " has total balance of: " << testBank.GetAccount(0)->GetBalance() << "czk." << endl;
    testBank.GetAccount(0)->Deposit(100);
    cout << "+100czk has been added to this account." << endl;
    cout << "Account owned by: " << testBank.GetClient(0)->GetName() <<
    " has total balance of: " << testBank.GetAccount(0)->GetBalance() << "czk.\n" << endl;
    
    //Withdraw 40czk
    cout << "Lets withdraw 40czk from Michal Rucka's account." << endl;
    testBank.GetAccount(0)->Withdraw(40);
    cout << "-40czk has been withdrew from this account." << endl;
    cout << "Account owned by: " << testBank.GetClient(0)->GetName() <<
    " has total balance of: " << testBank.GetAccount(0)->GetBalance() << "czk.\n" << endl;

    //Withdraw test
    cout << "Now lets test if the owner of this accont can withdraw more than he has on the account." << endl;
    cout << "Can he withdraw 240czk?" << endl;
    bool withdrawCheck = testBank.GetAccount(0)->CanWithdraw(240);
    if (withdrawCheck){
        cout << "Amount can be withdrew." << endl;
    }
    else{
        cout << "Amount cannot be withdrew.\n" << endl;
    }


    return 0;
}
