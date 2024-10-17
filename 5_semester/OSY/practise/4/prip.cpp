#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc < 2) exit(1);
    int numbers = atoi(argv[1]);

    int pipe1[2];
    pipe(pipe1);



    close(pipe1[0]);

    for(int i = 0; i<numbers; i++) {
      if(fork() == 0) {
        int num = rand() % 100;
        char buffer[100];
        sprintf(buffer, "%d. %d", i, num);
        printf("%s\n", buffer);
        write(pipe1[1], buffer, strlen(buffer));
        usleep(100000);
      }
      close(pipe1[1]);
    }
}