#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int main() {
    int pipe1[2], pipe2[2];

    pipe(pipe1);
    pipe(pipe2);

    if (fork() == 0) {
        int input_file = open("names.txt", O_RDONLY);
        if (input_file == -1) {
            perror("Chyba při otevírání vstupního souboru");
            exit(1);
        }

        dup2(input_file, STDIN_FILENO);
        dup2(pipe1[1], STDOUT_FILENO);

        close(pipe1[0]);
        close(pipe1[1]);
        close(pipe2[0]);
        close(pipe2[1]);
        close(input_file);

        execlp("sort", "sort", NULL);
        perror("Chyba při spouštění sort");
        exit(1);
    }

    if (fork() == 0) {
        dup2(pipe1[0], STDIN_FILENO);
        dup2(pipe2[1], STDOUT_FILENO);

        close(pipe1[0]);
        close(pipe1[1]);
        close(pipe2[0]);
        close(pipe2[1]);

        execlp("tr", "tr", "[a-z]", "[A-Z]", NULL);
        perror("Chyba při spouštění tr");
        exit(1);
    }

    if (fork() == 0) {
        dup2(pipe2[0], STDIN_FILENO);

        close(pipe1[0]);
        close(pipe1[1]);
        close(pipe2[0]);
        close(pipe2[1]);

        execlp("nl", "nl", "-s", ". ", NULL);
        perror("Chyba při spouštění nl");
        exit(1);
    }

    close(pipe1[0]);
    close(pipe1[1]);
    close(pipe2[0]);
    close(pipe2[1]);

    wait(NULL);

    return 0;
}