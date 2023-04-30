#include "account.hpp"


class Bank{
    private:
        Client** clients;
        int clientsCount;

        Account** accounts;
        int accountsCount;
    public:
        Bank(int c, int a){
            clients = new Client*[c];
            accounts = new Account*[a];
            clientsCount = 0;
            accountsCount = 0;
        }
        ~Bank(){
            //Delete clients
            for(int i=0; i<clientsCount; i++){
                delete clients[i];
            }
            delete[] clients;

            //Delete account
            for(int i=0; i<accountsCount; i++){
                delete accounts[i];
            }
            delete[] accounts;
        };

        Client* GetClient(int c){
            for(int i=0; i<clientsCount; i++){
                if (clients[i]->GetCode() == c){
                    return clients[i];
                }
            }
            return nullptr;
        };

        Account* GetAccount(int n){
            for (int i=0; i<accountsCount; i++){
                if (accounts[i]->GetNumber() == n){
                    return accounts[i];
                }
            }
            return nullptr;
        };

        Client* CreateClient(int c, string n){
            clients[clientsCount] = new Client(c, n);
            clientsCount++;
            return clients[clientsCount-1];
        }

        Account* CreateAccount(int n, Client *c){
            accounts[accountsCount] = new Account(n, c);
            accountsCount++;
            return accounts[accountsCount-1];
        }
        Account* CreateAccount(int n, Client *c, double ir){
            accounts[accountsCount] = new Account(n, c, ir);
            accountsCount++;
            return accounts[accountsCount-1];
        }
        Account* CreateAccount(int n, Client *c, Client *p){
            accounts[accountsCount] = new Account(n, c, p);
            accountsCount++;
            return accounts[accountsCount-1];
        }
        Account* CreateAccount(int n, Client *c, Client *p, double ir){
            accounts[accountsCount] = new Account(n, c, p, ir);
            accountsCount++;
            return accounts[accountsCount-1];
        }

        void AddInterest(){
            for (int i=0; i<accountsCount; i++){
                if (accounts[i]->GetInterestRate() != 0){
                    accounts[i]->AddInterest();
                }
            }
        };
};