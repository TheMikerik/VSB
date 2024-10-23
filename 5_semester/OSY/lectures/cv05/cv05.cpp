#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int main() {
    int pipe1[2], pipe2[2], pipe3[2];

    pipe(pipe1);
    pipe(pipe2);
    pipe(pipe3);

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
        close(pipe3[0]);
        close(pipe3[1]);
        close(input_file);

        execlp("awk", "awk", "{printf \"%02d %s\\n\", length, $0}", NULL);
        perror("[ERROR] Awk");

        exit(1);
    }

    if (fork() == 0) {
        dup2(pipe1[0], STDIN_FILENO);
        dup2(pipe2[1], STDOUT_FILENO);

        close(pipe1[0]);
        close(pipe1[1]);
        close(pipe2[0]);
        close(pipe2[1]);
        close(pipe3[0]);
        close(pipe3[1]);

        execlp("sort", "sort", NULL);
        perror("[ERROR] Sort");
        exit(1);
    }

    if (fork() == 0) {
        dup2(pipe2[0], STDIN_FILENO);
        dup2(pipe3[1], STDIN_FILENO);

        close(pipe1[0]);
        close(pipe1[1]);
        close(pipe2[0]);
        close(pipe2[1]);
        close(pipe3[0]);
        close(pipe3[1]);

        execlp("grep", "grep", "05 A", NULL);
        perror("[ERROR] Grep");
        exit(1);
    }
    if (fork() == 0) {
        dup2(pipe3[0], STDIN_FILENO);

        close(pipe1[0]);
        close(pipe1[1]);
        close(pipe2[0]);
        close(pipe2[1]);
        close(pipe3[0]);
        close(pipe3[1]);

        execlp("nl", "nl", "-s", ". ", NULL);
        perror("[ERROR] Nl");
        exit(1);
    }

    close(pipe1[0]);
    close(pipe1[1]);
    close(pipe2[0]);
    close(pipe2[1]);
    close(pipe3[0]);
    close(pipe3[1]);

    wait(NULL);

    return 0;
}