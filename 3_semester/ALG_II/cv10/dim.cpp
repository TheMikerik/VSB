#include <iostream>
#include <vector>

using namespace std;

struct number{
    int key;
    int value;

    number(int n) : key(n), value(1) { };
};


int main(){
    vector<number> n;

    for (int i = 0; i<2000; i++){
        n.push_back(i);
    }

    for (int i = 0; i<2000; i++){
        if (i % 8 == 5){
            n[i].value++;
            std::cout << n[i].key << " ";
        }
    }

    cout << "\n\n";

    for (int i = 0; i<2000; i++){
        if (i % 7 == 2){
            n[i].value++;
            std::cout << n[i].key << " ";
        }
    }

    cout << "\n\n";

    for (int i = 0; i<2000; i++){
        if ((i + 2) % 11 == 0){
            n[i].value++;
            std::cout << n[i].key << " ";
        }
    }

    cout << "\n\n";
    cout << "\n\n";
    cout << "\n\n";

    for (int i = 0; i<2000; i++){
        if (n[i].value == 4){
            std::cout << n[i].key << " ";
        }
    }
}