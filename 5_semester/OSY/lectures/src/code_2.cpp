#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main (int argn, char **argc) {
  int myPipe[ 2 ];
  pipe(myPipe);

  if (fork() == 0){
    dup2(myPipe[ 1 ], 1); // stdout
    close(myPipe[ 0 ]);
    close(myPipe[ 1 ]);
    execlp("ls", "ls", NULL);
    printf("This line will not be printed\n");
  }
  close(myPipe[ 1 ]);
  while (1){
    char buff[ 123 ];
    int ret = read(myPipe[ 0 ], buff, sizeof(buff));
    if (ret <= 0){
      break;
    }
    write(1, buff, ret);
  }
  wait(NULL);
}


/*

Strace:
  - Use 'sudo dtruss ./yt'

Duplicate:
  - Bere obsah z tabulky descriptoru z jednoho radku do druheho radku
  - Dva radky ukazuji na jednu rouru

Exec:
  - Pouzivame kdyz chceme v procesu prohodit program
  - 

-> pipe -> fork -> duplicate -> exec







// Jednoduche volani, ktere nahradi program v procesu
  // Piseme jako prvni argument cestu k programu, ktery chceme spustit
  // Druhy argument je nazev programu
  // Dalsi polozky jsou argumenty
  execlp("ls", "ls", NULL);
  // execlp("generator", "generator", "-b", "4", "10", NULL);

  // Za execlp program prestava existovat. Pokud tomu tak neni, tak se neprovedl spravne
  printf("This line will not be printed\n");
*/