#include <stdio.h>
#include <stdbool.h>

int main()
{
    bool muz = true;
    bool zena = false;
    bool rodic = true;

    bool clovek = muz || zena;
    bool otec = rodic && !zena;

    int cislo = 5;
    bool cislo_je_sude = ((cislo % 2) == 0);

    int DelkaHesla = 4;
    int VelkaPismena = 0;
    int MalaPismena = 4;

    bool KratkeHeslo = (DelkaHesla < 5);
    bool SpravneHeslo = (DelkaHesla > 4) && (VelkaPismena > 0) && (MalaPismena > 0);

    /* ULOHA: Absolutní hodnota */
    /* Pokud je zadané číslo záporné, tak z něj udělej absolutní hodnotu */
    int cis = -105;
    if (cis < 0)
    {
        cis = (cis * (-1));
        // nebo
        // cis *= -1;
    }

    printf("%d\n\n", cis);

    /* Pokud je zadané číslo 1, tak jej nastav na 0. A naopak*/
    int cislo2 = 0;
    if (cislo2 == 0)
    {
        cislo2 = 1;
    }
    else if (cislo2 == 1)
    {
        cislo2 = 0;
    }
    else
        printf("Chyba");

    printf("%d\n\n", cislo2);

    /* Vypocti dan
        plat mensi 10 000czk je 18%
        plat mensi 20 000czk je 20%
        plat vetsi 20 000czk je 30%
    */

    int plat;
    printf("Zadej svůj plat: \n");
    scanf("%d", &plat);

    if (plat < 10000)
    {
        printf("Tvá daň je 18 procent\n\n");
    }
    else if (plat >= 10000 && plat < 20000)
    {
        printf("Tvá daň je 20 procent\n\n");
    }
    else if (plat >= 20000)
        printf("Tvá daň je 30 procent\n\n");

    /*Pokud je cislo A větší než B, tak jej odečti. Nebo naopak*/
    int A = 30;
    int B = 54;
    int rozdil = 0;

    if (A > B)
        rozdil = A - B;
    else
        rozdil = B - A;

    rozdil = (A > B) ? (A - B) : (B - A);



    



    /* Vypiš název dne dle čísla v týdny */
    int den = 3;

    switch (den)
    {
        case 1:    printf("Pondělí"); break;       // Break musí být na konci každého bloku
        case 2:    printf("Úterý"); break;
        case 3:    printf("Středa"); break;
        case 4:    printf("Črtvrtek"); break;
        case 5:    printf("Pátek"); break;
        case 6:    printf("Sobota"); break;
        case 7:    printf("Neděle"); break;
        default: printf("Nesprávný den v týdnu");  //Default se nám zobrazí pokud zadáme špatné číslo, které je mimo náš rozsah;
    }
    printf("\n\n");
    return 0;
}

/*
&& = and
|| = or
! = not
*/