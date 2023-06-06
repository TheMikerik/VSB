#include <stdio.h>

int a, b;

int scitani()
{
    return a + b;
}

int odcitani()
{
    return a - b;
}

int main()
{
    a = 8;
    b = 3;
    printf("%d\n", scitani());
    printf("%d\n", odcitani());
}