#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int main (int argc, char* argv[]){
    int buffer_size = 1000;
    char* buffer = (char*)malloc(sizeof(char) * buffer_size);

    strcpy(buffer, "Nejaky retezec\ndalsi radek\na dalsi rndm radek\n");

    FILE* fout = fopen("input.bin", "w");

    int cislo = 1000000;

    fwrite(buffer, sizeof(char), strlen(buffer), fout); // Toto je binární zápis
    fwrite(&cislo, sizeof(int), 1, fout);

    int cislo_1 = 2, cislo_2 = 50;
    fprintf(fout, "Dve cisla:\n%d, %d", cislo_1, cislo_2);

    fclose(fout); 

    FILE* fin = fopen("input.bin", "r");

    int cislo_3, cislo_4;

    fread(buffer, sizeof(char), buffer_size, fin);
    fclose(fin);
    printf("%s", buffer);
    free(buffer);
    buffer = NULL;

    return 0;
}