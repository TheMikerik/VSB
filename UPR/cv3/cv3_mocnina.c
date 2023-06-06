#include <stdio.h>
#include <math.h>

// funkce mocnina, kde na vstupu je hodnota a exponent, fce vrati xtu mocninu
void mocninaFCE(int hodnota, int exponent, int mocnina)
{
    mocnina = pow(hodnota, exponent);
    printf("%d", mocnina);
}


int main ()
{
    printf("%d\n",mocninaFCE(2,4,8));
}
