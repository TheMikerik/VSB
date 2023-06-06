#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef struct{
    
    void** data; //ukazovatel na ukazovatel
    int capacity;
    int count;
} GenArray;

//
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

int main(){
    GenArray c;
    gen_array_init(&c, 5);

    char * arr = malloc(5* sizeof(char));
    strcpy(arr, "Ahoj");
    gen_array_add_dynamic(&c, arr);

    char * arr2 = malloc(5* sizeof(char));
    strcpy(arr2, " svet");
    gen_array_add_dynamic(&c, arr2);



    int add = 2;
    for (int i = 0; i < 2; i++){
        int* number = malloc (sizeof(int));
        *number = i;   

        gen_array_add_dynamic(&c, number);
        add= add*2;
    }

    printf("Capacity is %d; Number of data: %d\n", c.capacity, c.count);
    for (int i=0; i<c.count; i++){
        printf("%s\n", arr, (char *)gen_array_get(&c, i)); // & adresa * -> ziskam hodnotu z ukazovatele
    }

    return 0;
}