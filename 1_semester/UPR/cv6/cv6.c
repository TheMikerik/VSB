#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #1 Create function, where the input will be char and it will print 'Znak X ma ciselny kod Y'
void vypisZnak(char znak){
    printf("Znak %c má číselný kód %d\n", znak, znak);
}

// #2 Array made out of chars
void vypis_retazca(){
    char array [] = {'A', 'H', 'O', 'J', '\0'} ; // The end of the array must have \0 !! --> It signalize end of the array
    printf("%s\n", array);

    char array2[] = "HELLO";
    printf("%s\n", array2);

    char array3[10];
        array3[0] = 'H';
        array3[1] = 'E';
        array3[2] = 'L';
        array3[3] = 'L';
        array3[4] = 'O';
        array3[5] = '\0';
    printf("%s\n", array3);
}

// #3 Print dynamic array that says "Hello world" and then delete it
void vypisDynamickyRetezec(int delka){
    char*  dyn_retazec = malloc(delka * sizeof(char));

    scanf("%s", dyn_retazec);
    printf("%s", dyn_retazec);

    free(dyn_retazec);

}

// #4 New functions
void ret_fce(){
    char ret1[] = "Ahoj";
    char ret2[] = "svet !";

    // strlen --> ftion wheres output is length of the array ||  %ld = long d
    printf("Delka retezce ret1 je %ld.\n", strlen(ret1));

    // strcpy --> ftion that copy array to OUTPUT from INPUT
    char ret3[10];
    strcpy(ret3, ret2);
    printf("Obsah ret3 je %s\n", ret3);

    // strcat --> concatenation = spojení --> ftion that will concat two arrays
    char ret4[50];
    strcpy(ret4, ret1);
    strcat(ret4, ret2);
    printf("Obsah ret4 je %s\n", ret4);

    //strcmp --> compare --> ftion will compare two different arrays
    if (strcmp(ret1, ret2) == 0){
        printf ("Retazce jsou stejné! \n");
    }
    else {
        printf ("Retazce jsou jiné! \n");
    }
}

// #5 Exercise
void myStrlen(char* ret){
    int i = 0;
    while ( ret[i] != '\0'){
        i++;
    }
    printf("Delka retezce je %d\n", i);
}
void myStrcpy(char* ret2, char* src){
    for (int i = 0; src[i] != '\0'; i++){
        ret2[i] = src[i];
    }
    printf("%s", ret2);
}
void myStrcat(char* ret, char* ret2){

}
void myStrcmp(char* ret1, char* ret2){

}

int main (){
    /*
    char znak = 'c';

    printf("%c\n", znak);
    printf("%d\n", znak);

    vypisZnak(znak); // #1
    vypis_retazca(); // #2

    int delka; // #3
    printf("Zadej delku retezce: ");
    scanf("%d", &delka);
    vypisDynamickyRetezec(delka); */

    // #4 
    /*
    ret_fce();

    printf("\n\n");    
    return 0;*/

    // #5
    char ret[] = "Hello world! Means in Czech language: Ahoj světe!";
    printf("%s\n", ret);
    myStrlen(ret);

    char src[] = "C-lan is muuuch easier than Haskel";
    char ret2[0];
    myStrcpy(ret2, src);



    printf("\n\n");    
    return 0;
}