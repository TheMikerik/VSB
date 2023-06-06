#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #1 Napiste funkci plus, která bude mít na vstupu dvě čísla A a B a bude vracet jejich součet
int plus (int a, int b){
    return a + b;
}



// #2 Napiste funkci aritmetika, ktera vrati soucet, soucin, podíl a rozdíl dvou císel
void aritmetika1 (int a, int b, int* soucet, int* soucin, int* podil, int* rozdil){
    *soucet = a + b;
    *soucin = a * b;
    *podil = a / b;
    *rozdil = a - b;
}



// #3 Lehčí řešení dvojky pomocí struktury
typedef struct{
    int a;
    int b;
    int soucet;
    int soucin;
    int podil;
    int rozdil;
} aritmetika2;

aritmetika2 aritmetika3 (int a, int b){
    aritmetika2 ar;
    ar.soucet = a + b;
    ar.soucin = a * b;
    ar.podil = a / b;
    ar.rozdil = a - b;

    return ar;
}



// #5 Chceme vložit tri osoby, u kterych chceme evidovat jmeno, prezdivku a rok narozeni
typedef struct{
    char jmeno[50];
    char prezdivka[50];
    int rok_narozeni;
} osoba;

void vypis_osoby2 (osoba o){ // - vtváříme novou kopii osoby, která se dá měnit pouze v tomto voidu (jinde zůstává stejná)
    printf("Jmeno osoby je %s", o.jmeno); // bez pointeru používáme .
}

void vypis_osoby3 (osoba* o){ // - odkazujeme na osobu, a pokud ji zde změníme, tak se změní všude
    printf("Jmeno osoby je %s", o->jmeno); // s pointrem používáme ->
}


// #6 Struktura ve strukture, ve strukture, ...
typedef struct{
    char ulice[50];
    char mesto[50];
    char psc[6];
    char stat[30];
    osoba Osoba;
} Adresa;

void vypis_osoby2 (osoba* o){
    printf("Jmeno osoby je %s", o.osoba.mesto);
}






int main(){
    int soucet1 = plus(5,3); // #1

    int podil;  // #2
    int soucet;  // * z pointra udělá hodnotu, & z hodnotz udělá pointer
    int soucin;
    int rozdil;
    aritmetika1(5,3, &soucet, &soucin, &podil, &rozdil);
    printf("%d %d %d %d\n", soucet, soucin, podil, rozdil);

    aritmetika3(5,3); // #3
    aritmetika2 vysledek = aritmetika3(5,3);
    vysledek.soucet;
    vysledek.soucin;
    vysledek.podil;
    vysledek.rozdil;
    printf("%d %d %d %d\n", vysledek.soucet, vysledek.soucin, vysledek.podil, vysledek.rozdil);

    char jmena [3][50]; // #4
        strcpy(jmena[0], "Pavel");
        strcpy(jmena[1], "Richard");
        strcpy(jmena[2], "Tomas");
    char prezdivka [3][50];
        strcpy(prezdivka[0], "Pavelos");
        strcpy(prezdivka[1], "Richardos");
        strcpy(prezdivka[2], "Tomasos");
    int rok_narozeni[3];
        rok_narozeni[0] = 2000;
        rok_narozeni[1] = 2001;
        rok_narozeni[2] = 2002;

    for (int i = 0; i  < 3; i++){
        printf("%s %s %d\n", jmena[i], prezdivka[i], rok_narozeni[i]);
    }

    osoba pole_osob[3]; // #5 Zjednodušená 4

    strcpy(pole_osob[0].jmeno,"Petr");
    strcpy(pole_osob[0].prezdivka,"Novak");
    pole_osob[0].rok_narozeni,1938;


    return 0;
}