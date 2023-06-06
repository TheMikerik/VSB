#include <stdio.h>
#include <string.h>

/*      #1 Vytvor strukturu student, ktera bude obsahovat:
            login - 7
            jmeno - 30
            prijimeni - 30
            email - 60
            vek
            uctovy_zustatek
        #2 vytvor funkci novy_student(login, jmeno, prijimeni, vek) a vypis ho
        #3 vytvor funkci vloz_penize(student, castka)
        #4 vytvor funkci prumerny_vek
        #5 vytvor funkci hledej_studenta podle loginu
*/
typedef struct
{
    char login[7];
    char jmeno[30];
    char prijimeni[30];
    char email[60];
    int vek;
    int uctovy_zustatek;
}student;

student novy_student(char login, char jmeno, char prijimeni, int vek){
    student st[5];
    
    int i = 0;
    while (i < 5){
    strcpy(st[i].login,"ruc0066");
    strcpy(st[i].jmeno,"Michal");
    strcpy(st[i].prijimeni,"Rucka");
    strcpy(st[i].email,"email");


    i++;
    }

}



int main(){
}