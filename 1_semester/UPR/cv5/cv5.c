#include <stdio.h>
#include <stdlib.h>

void matice(int radky, int sloupce){
    int* matice = (int*)malloc(sizeof(int) * radky * sloupce);
    for (int i = 0; i < radky; i++){
        for (int j = 0; j < sloupce; j++){
            matice[i * sloupce + j] = i * j;
        }
    }

    for (int i = 0; i < radky; i++){
        for (int j = 0; j < sloupce; j++){
            printf("%d ", matice[i * sloupce + j]);
        }
        printf("\n");
    }
    


    free(matice);
}
void reorder(int *pole, int pocet){
    for (int poradi = 0; poradi <= pocet; poradi++){
        printf("%d ", pole[pocet - poradi]);
    }
}
void napln_pole(int* pole, int pocet){
    for (int i = 0; i < pocet; i++){
        pole[i] = i;
    }
}
void vypis_pole(int* pole, int pocet){
    for (int x = 0; x < pocet; x++){
        printf("%d ", pole[x]);
    }
}
int main(){

    matice(6, 10);
    /*
    int pocet;
    printf("Zadej kolik má být polí: ");
    scanf("%d", &pocet);

    int pole[pocet]; //-----> statické pole
    reorder(pole, pocet);
    // int* pole = (int*)malloc(sizeof(int) * 1000);       // -------> dynamické pole

    */
  //  reorder(pole, pocet);

    /*
    napln_pole(pole, pocet);
    vypis_pole(pole, pocet);
    */

  //  free(pole); // ---------------------------------------> funkce, která slouží na vymazání paměti !!! VZDYY UVOLNIT !!!

    // -------> gcc cv5.c -fsanitize=address -o cv5    -----> zjistí chzbu

    return 0;
}