// zde se píše kód od array.h
#include "array.h"
#include <stdlib.h>

void gen_array_init(GenArray* array, int capacity){
    array->data = malloc(capacity * sizeof(void*)); // void* protoze v GenArray je to definovano jako pointer
    array->capacity = capacity;
    array->count = 0;
}

void gen_array_add_dynamic(GenArray* array, void* added_value){
    if (array->count == array->capacity){
        array->capacity *= 2; // *= znamená: vynásob to tím, co je za *=
        array->data = realloc(array->data , array->capacity * sizeof(void*)); // realloc - neco jako malloc, akorát pri dynamickém poli
    }  
    array->data[array->count] = added_value;
    array->count++;
}

void* gen_array_get(GenArray* array, int order){
    //printf("Value on the position %d is %d\n", order, array->data[order]);
    return array->data[order];
}

void gen_array_remove(GenArray* array){
    for (int i = 0; i <array->count; i++){ 
        free(array->data[i]);
        array->data[i] = NULL;
    }
    free(array->data);
    array->data = NULL;

}