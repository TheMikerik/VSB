#include <stdio.h>

//Napis fci ktera ma na vstupu vysku a sirku a bude vracet obsah
int ObsahObdelniku(int sirka, int vyska)
{
    int obsah = sirka * vyska;
    return obsah;

}

int main()
{
    int obsah = ObsahObdelniku(5,8);
    printf ("%d", ObsahObdelniku(5,8));
}