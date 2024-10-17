#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s N\n", argv[0]);
        exit(1);
    }

    int N = atoi(argv[1]);

    int pipe1[2], pipe2[2], pipe3[2];

    pipe(pipe1);
    pipe(pipe2);
    pipe(pipe3);

    // První potomek
    if (fork() == 0) {
        close(pipe1[1]);
        close(pipe2[0]);
        close(pipe3[0]);
        close(pipe3[1]);

        char buffer[100];
        while (read(pipe1[0], buffer, sizeof(buffer)) > 0) {
            int id, num1, num2;
            char operation;
            sscanf(buffer, "%d. %d", &id, &num1);
            operation = (rand() % 2 == 0) ? '+' : '-';
            num2 = rand() % 100;
            snprintf(buffer, sizeof(buffer), "%d. %d %c %d\n", id, num1, operation, num2);
            write(pipe2[1], buffer, strlen(buffer) + 1);
            printf("První potomek (PID: %d): Přijato od rodiče a odesláno: %s", getpid(), buffer);
        }

        close(pipe1[0]);
        close(pipe2[1]);
        exit(0);
    }

    // Druhý potomek
    if (fork() == 0) {
        close(pipe1[0]);
        close(pipe1[1]);
        close(pipe2[1]);
        close(pipe3[0]);

        char buffer[100];
        while (read(pipe2[0], buffer, sizeof(buffer)) > 0) {
            int id, num1, num2, result;
            char operation;
            sscanf(buffer, "%d. %d %c %d", &id, &num1, &operation, &num2);
            result = (operation == '+') ? (num1 + num2) : (num1 - num2);
            snprintf(buffer, sizeof(buffer), "%d. %d %c %d = %d\n", id, num1, operation, num2, result);
            write(pipe3[1], buffer, strlen(buffer) + 1);
            printf("Druhý potomek (PID: %d): Výpočet a odeslání: %s", getpid(), buffer);
        }

        close(pipe2[0]);
        close(pipe3[1]);
        exit(0);
    }

    // Třetí potomek
    if (fork() == 0) {
        close(pipe1[0]);
        close(pipe1[1]);
        close(pipe2[0]);
        close(pipe2[1]);
        close(pipe3[1]);

        char buffer[100];
        while (read(pipe3[0], buffer, sizeof(buffer)) > 0) {
            printf("Třetí potomek (PID: %d): Přijatý výsledek: %s\n", getpid(), buffer);
        }

        close(pipe3[0]);
        exit(0);
    }

    close(pipe1[0]);
    close(pipe2[0]);
    close(pipe2[1]);
    close(pipe3[0]);
    close(pipe3[1]);

    srand(time(NULL));
    for (int i = 1; i <= N; i++) {
        int num = rand() % 100;
        char buffer[100];
        snprintf(buffer, sizeof(buffer), "%d. %d\n", i, num);
        write(pipe1[1], buffer, strlen(buffer) + 1);
        printf("Rodič (PID: %d): Generováno a odesláno: %s", getpid(), buffer);
        usleep(100000);
    }

    close(pipe1[1]);

    wait(NULL);
    wait(NULL);
    printf("Rodič (PID: %d): Všichni potomci dokončili práci.\n", getpid());
    return 0;
}