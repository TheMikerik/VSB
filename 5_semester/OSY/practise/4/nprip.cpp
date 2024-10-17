#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc < 2) exit(1);
    int numbers = atoi(argv[1]);
    srand(time(NULL));

    int pipe1[2], pipe2[2], pipe3[2];
    pipe(pipe1);
    pipe(pipe2);
    pipe(pipe3);

    if (fork() == 0) {
        close(pipe1[1]);
        close(pipe2[0]);
        close(pipe3[0]);
        close(pipe3[1]);
        char buffer[100];
        char op = rand() % 2 == 0 ? '+' : '-';
        int num = rand() % 100;
        while (read(pipe1[0], buffer, sizeof(buffer)) > 0) {
            printf("%s%c%d\n", buffer, op, num);
            write(pipe2[1], buffer, strlen(buffer)+1);
        }
        exit(0);
    }

    if (fork() == 0) {
        // close(pipe1[0]);
        // close(pipe1[1]);
        // close(pipe2[1]);
        // close(pipe3[0]);
        // char buffer[100];
        // char op;
        // int a, b, c, result;
        // while (read(pipe2[0], buffer, sizeof(buffer)) > 0) {
        //     sscanf(buffer, "%d. %d%c%d\n", &a, &b, &op, &c);
        //     if (op == '+') result = b + c;
        //     sprintf(buffer, "%d. %d%c%d=%d\n", a, b, op, c, result);
        //     write(pipe3[1], buffer, strlen(buffer)+1);
        // }
        // exit(0);
    }

    if (fork() == 0) {
        // close(pipe1[0]);
        // close(pipe1[1]);
        // close(pipe2[0]);
        // close(pipe2[1]);
        // close(pipe3[1]);
        // char buffer[100];
        // while (read(pipe3[0], buffer, sizeof(buffer)) > 0) {
        //     printf("%s", buffer);
        // }
        // exit(0);
    }

    close(pipe1[0]);
    close(pipe2[0]);
    close(pipe2[1]);
    close(pipe3[0]);
    close(pipe3[1]);

    wait(NULL);

    for(int i = 1; i <= numbers; i++) {
        int num = rand() % 100;
        char message[100];
        sprintf(message, "%d. %d\n", i, num);
        write(pipe1[1], message, strlen(message)+1);
        usleep(1000000);
    }
    close(pipe1[1]);

}