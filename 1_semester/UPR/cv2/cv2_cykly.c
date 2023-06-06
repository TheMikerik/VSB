#include <stdio.h>

int main()
{
    // Vypiš čísla 1 az 15 s použitím cyklu for
    for (int i = 1; i < 16; i++) // Prnví: deklaruju proměnnou....Druhá: Podmínka do kdy běží cyklus....Třetí:
    {
        printf("%d\n", i);
    }

    // Narozdíl od předešlého kódu "int i" bude rozpoznán i mimo "for" podmínku
    int i = 1;
    for (; i < 16;)
    {
        printf("%d\n", i++);
    }

    i = 0;
    while (i < 16)
    {
        i++;
        printf("%d\n", i);
    }

    // Vnořeny cyklus
    // Vypis 10 řádků s číslami od 1 do 15

    int cislo = 0;
    int radky = 0;
    while (radky < 15)
    {
        radky++;
        for (int i = 1; i < 16; i++)
        {
            printf("%d", i);
        }
        printf("\n");
    }
}
