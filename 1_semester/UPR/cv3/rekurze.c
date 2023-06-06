#include <stdio.h>

int faktorial(int cislo)
{
    if (cislo > 1)
        return cislo * faktorial(cislo - 1);
    else
        return 1;
}

int main()
{
    printf("%d\n", faktorial(10));
}