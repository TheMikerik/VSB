#include <stdio.h>
/*
int main()
{
    VypisObdelnik(5, 8);
    return 0;
}

int VypisObdelnik(int sirka, int vyska) // fce s parametrem
{
    for (int i = 0; i < vyska; i++)
    {
        for (int j = 0; j < sirka; j++)
        {
            printf("x");
        }
        printf("\n");
    }
}
*/

int main()
{
    NaformatujDatum(2003,8,6);
}

int NaformatujDatum(int rok, int mesic, int den, int format)
{
    printf("Zadej pozadovany format:\n1 - den.mesic.rok\n2 - rok/mesic/den\n3 - rok-mesic-den\n");
    scanf("%d", &format);
    if (format == 1)
    {
        printf("%d.%d.%d\n", den, mesic, rok);
    }
    else if (format == 2)
    {
        printf("%d/%d/%d\n", rok, mesic, den);
    }
    else if (format == 3)
    {
        printf("%d-%d-%d\n", rok, mesic, den);
    }
    else
    {
        printf("Vybral sis nespravny format!\n");
    }
    
}
