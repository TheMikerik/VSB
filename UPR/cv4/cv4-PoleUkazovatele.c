#include <stdio.h>

void Pole(){
    int pole[5]; // Do [] píšeme kolik hodnot se dané proměnné bude nacházet 
        pole[0] = 5;
        pole[1] = 6;
        pole[2] = 4;
        pole[3] = 8;
        pole[4] = 9;
    for (int i = 0; i < 5; i++){
        printf("Pole má hodnotu %d na indexu %d\n", pole[i], i);
    }    
}

void Pole2(){
    int pole[] = {4,10,20,30,50,10,66,55,77};
    
}

/* Vytvoř funkci statistikz, v rámci které vztvoříte pole o 10 prvcích a vzpíšete na obrazovku min, max a průměr */
void statistika(){
    int stats[10] = {12,48,35,98,1,2,0.65,999,651,89};
    int min = 0, max = 0;

    for (int i = 0; i != 10; i++){
        if (stats[i+1] > stats[i]){
            min = stats[i];
        }
        else{
            min = stats[i+1];
        }
    }
    
    for (int iMAX = 0; iMAX < 9; iMAX++){
        max = stats[iMAX];
        if (max > stats[iMAX+1]){
            max = stats[iMAX];
        }
        else {
            max = stats [iMAX+1];
        }

    }
    printf("Min je: %d\n", min);
    printf("Max je: %d\n", max);
}

/* Vytvoř fci fibbonacci, v rámci které vytvoříte pole o 10 prvcích a dvě první hodnotz nastavíte na 0 a 1.
Každá další hodnota bude nastavena jako součet dvou předešlých. */
void fibonacci(){
    int fibon[10] = {0,1};
    printf("Fibonacciho číslo na pozici 1 je %d\n", fibon[0]);
    for (int i = 2; i < 11; i++){
        fibon[i] = fibon[i-1] + fibon[i-2];
        printf("Fibonacciho číslo na pozici %d je %d\n", i, fibon[i]); 
    }
}

int main(){
    printf("Cvičení 4 - Pole a ukazovatele\n");
    statistika();
    //fibonacci();
    return 0;
}