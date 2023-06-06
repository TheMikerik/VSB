#include <stdio.h>

void pointer(){
    int a = 10;
    int* pa = &a;  // * odkazuje na pointer

    printf("Hodnota a je %d\n", a);
    printf("Adresa a je %d\n", pa);
    printf("Hodnota a je %d\n", *pa);

    a = 20;
    *pa = 30;

    printf("Hodnota a je %d\n", a);
    printf("Adresa a je %d\n", pa);
    printf("Hodnota a je %d\n", *pa);
}

void swap(int* pa, int* pb){  // int* pa a int *pb jsou pointry - pa -> pointer na a
    int tempSwapA = *pa;
    *pa = *pb;
    *pb = tempSwapA;
}

void pole_pointer(){
    int pole[] = {10,20,30,40};
    int* ptr = pole;

    printf("Hodnota na pozici 0 je %d\n", pole[0]);
    printf("Hodnota na pozici 1 je %d\n", pole[1]);

    printf("Hodnota na pozici 0 je %d\n", ptr[0]);
    printf("Hodnota na pozici 0 je %d\n", ptr[1]);
}

/* Napiš funkci suma, které bude vracet součet hodnot v předaném poli */

/*
int suma(int* pole, int pocet){
    int suma = 0;
    for (int i = 0; i < pocet, i++); {
        int suma = suma + pole[i];
    }
    printf("Suma pole je: %d", suma);
}
*/

// Napiš funkci init, která bude mít na vstupu pole a inicialiyuje ho na hodnotu predanou parametrem
void init(int* pole){
    int n = scanf(printf("Pol)
    for (int i = 0; i < 4; i++){
        pole[i] = n;
    }

}

int main(){
    int a = 10;
    int b = 20;

    swap(&a, &b); // Díky tomuto získám hodnotu z pointru
    printf("Hodnota a je: %d a hodnota b je: %d\n", a, b);
    
    pole_pointer();

    ;
    return 0;
}