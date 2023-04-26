#include <iostream>
#include <iomanip>
#include <math.h>

using namespace std;

int main(){
    int x {12345678};
    double y {1.005};
    long z = {456};
    float a = {-126.496};

    cout << setprecision(10);
    cout << hex << x << endl;
    cout << hex << y << endl;
    cout << a << endl;

    cout << setprecision(4);
    cout << ceil(a) << endl;
    cout << floor(a) << endl;
    cout << abs(a) << endl;

    cout << log10(30) << endl;
    cout << log(300) << endl;
    cout << exp10(3) << endl;
    cout << exp(300) << endl;



    return 0;
}