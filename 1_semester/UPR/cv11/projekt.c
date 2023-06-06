#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "array.h"

typedef struct{
    int* data;
    int capacity;
    int count;
} Array;

//
void array_init(Array* array, int capacity){
    array->data = malloc(capacity * sizeof(int));
    array->capacity = capacity;
    array->count = 0;
}

void array_add(Array* array, int added_value){

    assert(array->count < array->capacity);     // Neco jako if. Pokud podmínka platí, tak dovolí programu jet dále, ale jakmile podmínka přestane palatit, tak na tomto řádku vyhodí chybu
        array->data[array->count] = added_value;
        array->count++;
}

void array_add_dynamic(Array* array, int added_value){
    if (array->count == array->capacity){
        array->capacity *= 2; // *= znamená: vynásob to tím, co je za *=
        array->data = realloc(array->data , array->capacity * sizeof(int)); // realloc - neco jako malloc, akorát pri dynamickém poli
    }  
    array->data[array->count] = added_value;
    array->count++;
}

int array_get(Array* array, int order){
    printf("Value on the position %d is %d\n", order, array->data[order]);
}

void array_remove(Array* array){
    free(array->data);
    array->data = NULL;
}

int main(){
    Array a;
    array_init(&a, 5);

    int add = 2;
    for (int i = 0; i < 10; i++){
        array_add_dynamic(&a, add);
        add= add*2;
    }

    for (int i=0; i<a.count; i++){
        array_get(&a, i);
    }
    

    return 0;
}