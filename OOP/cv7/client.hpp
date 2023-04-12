#include <iostream>
#include <string>

using namespace std;

class Client
{
private:
    static int clientCount;
    int code;
    string name;

public:
    Client(int c, string n)
    {
        code = c;
        name = n;
        clientCount++;
    }
    ~Client()
    {
        clientCount--;
    };

    static int GetClientCount();

    int GetCode()
    {
        return code;
    };

    string GetName()
    {
        return name;
    };
};

int Client::clientCount = 0;

int Client::GetClientCount(){
    return Client::clientCount;
};

