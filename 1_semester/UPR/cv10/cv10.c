#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// vytvor funkci
// vztvori binarni soubor a zapise do nej obsah pole a delku pole
void file_write(char* file_name){
    int array[] = {10,9,8,7,6,5,4,3,2,1};
    int array_length = 10;

    FILE *file = fopen(file_name, "wb");
    fwrite(&array_length, sizeof(int), 1, file);
    fwrite(array, sizeof(int), array_length, file);

    fclose(file);
}

// nacte soubor a naplni pole
void file_read(char* file_name){
    int array[10];
    int array_length = 10;

    FILE *file = fopen(file_name, "rb");
    fread(&array_length, sizeof(int), 1, file);
    fread(array, sizeof(int), array_length, file);

    fclose(file);

    for (int i = 0; i < array_length; i++){
        printf("%d ", array[i]);
    }
}

int main (){
    file_write("test.bin");
    file_read("test.bin");
}