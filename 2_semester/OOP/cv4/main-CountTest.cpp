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
    testBank.CreateAccount(1, testBank.GetClient(1), 2.17);
    testBank.CreateAccount(2, testBank.GetClient(2), testBank.GetClient(4));
    testBank.CreateAccount(3, testBank.GetClient(3), testBank.GetClient(5), 3.58);

    //Print clients
    cout << "Program will print names of all clients" << endl;
    for (int i=0; i<Client::GetClientCount(); i++){
        cout << "     Client_" << i << " -->   " << testBank.GetClient(i)->GetName() << endl;
    }

    //Print account owners
    cout << "\nProgram will print all accounts and its owner (and partner)" << endl;
    for (int i=0; i<Account::GetAccountCount();i++){
        if (testBank.GetAccount(i)->GetPartner()){
            cout << "     Account_" << testBank.GetAccount(i)->GetNumber() << " -->   ";
            cout << testBank.GetAccount(i)->GetOwner()->GetName() <<
            " + " << testBank.GetAccount(i)->GetPartner()->GetName() << endl;
        }
        else {
            cout << "     Account_" << testBank.GetAccount(i)->GetNumber() << " -->   ";
            cout << testBank.GetAccount(i)->GetOwner()->GetName() << endl;
        }
    }

    cout << "\nProgramm gonna display total number of clients and accounts\n";
    cout << "     Current number of clients is " << Client::GetClientCount() << endl;
    cout << "     Current number of accounts is " << Account::GetAccountCount() << endl;


    cout << "\nLets check the interest rate on those accounts\n";
    for (int i=0; i<Account::GetAccountCount();i++){
        if (testBank.GetAccount(i)->GetInterestRate()){
            cout << "     Account_" << testBank.GetAccount(i)->GetNumber() <<
            " has interest rate: " << testBank.GetAccount(i)->GetInterestRate()
            << "%" << endl;
        }
        else{
            cout << "     Account_" << testBank.GetAccount(i)->GetNumber() <<
            " has no interest rate.\n";
        }
    }

    cout << "\nLets set the same interest rate to account without interest rate\n";
    cout << "Select the interest rate: (double format) -->   ";
    double interest;
    cin >> interest;
    for (int i=0; i<Account::GetAccountCount();i++){
        if (!testBank.GetAccount(i)->GetInterestRate()){
            testBank.GetAccount(i)->SetInterestRate(interest);
        }
    }

    cout << "\nLets check the interest rate again\n";
    for (int i=0; i<Account::GetAccountCount();i++){
        if (testBank.GetAccount(i)->GetInterestRate()){
            cout << "     Account_" << testBank.GetAccount(i)->GetNumber() <<
            " has interest rate: " << testBank.GetAccount(i)->GetInterestRate()
            << "%" << endl;
        }
        else{
            cout << "     Account_" << testBank.GetAccount(i)->GetNumber() <<
            " has no interest rate.\n";
        }
    }

    cout << "\n\n";
    return 0;
}