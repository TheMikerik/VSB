#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char* argv[]){
    int buffer_size = 1000;
    char* buffer = (char*)malloc(sizeof(char) * buffer_size);

    strcpy(buffer, "Nejaky retezec\ndalsi radek\na dalsi rndm radek");

    FILE* fout = fopen("input.txt", "w");
    //fputs(buffer, fout); // Dá se nahradit fcí fprintf kde na prvním místě je lokace dokumentu a na druhém je klasický text jak známe z printf
    int cislo_1 = 2, cislo_2 = 50;
    fprintf(fout, "Dve cisla:\n%d, %d", cislo_1, cislo_2);

    fclose(fout); 

    FILE* fin = fopen("input.txt", "r");
    // 1) nazev souboru popr cesta k nemu - na pripone nezalezi
    // 2) moznost jak danz soubor otevrit
    //    r - read; w - úprava; a - dodatek (zapisuje nové věci na konec - např. log)
    //    možnost přidát x k W nebo k A -> wx, ax -> vytvoří kopii daného souboru -> jinak hrozí jeho nevratné přepsání
    
    // Soubor se snažíme udržet co nejkratší dobu otevřený. Pokud ho chceme nějak editovat nebo
    // upravovat, tak je vhodnější to udělat po zavření dokumentu -> výpadek sítě

    // Dávat pozor na načítání vstupu ze souborů -> z .txt to načítá 2x poslední řádek

    int cislo_3, cislo_4;
    fscanf(fout, "%d %d", &cislo_3, &cislo_4);

    while(!feof(fin)){ // feof = file end of the file
        fgets(buffer, buffer_size, fin);
        printf("%s", buffer);
    }
    fclose(fin);
    free(buffer);
    buffer = NULL;

    return 0;
}