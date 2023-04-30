#include <iostream>
#include <string>

using namespace std;

class Client{
    private:
        int code;
        string name;
    public:
        Client(int c, string n){
            code = c;
            name = n;
        }

        int GetCode(){
            return code;
        };

        string GetName(){
            return name;
        };
};