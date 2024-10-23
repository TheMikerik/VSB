#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Invalid parameters: %s <file_path> <ignored_char>\n", argv[0]);
        exit(1);
    }

    std::string file_path = argv[1];
    std::string ignored_char = argv[2];

    int out_bytes = 0;

    int pipe1[2], pipe2[2];

    pipe(pipe1);
    pipe(pipe2);

    if (fork() == 0) {
        int input_file = open(file_path.c_str(), O_RDONLY);
        if (input_file == -1) {
            perror("Chyba při otevírání vstupního souboru");
            exit(1);
        }

        char buffer[1024];
        int bytes_read, total_bytes = 0;

        while ((bytes_read = read(input_file, buffer, sizeof(buffer))) > 0) {
            total_bytes += bytes_read;
            write(pipe1[1], buffer, bytes_read);
        }
        out_bytes = total_bytes;
        fprintf(stderr, "Pocet predanych bajtu: %d\n", total_bytes);

        close(pipe1[1]);
        close(pipe1[0]);
        close(pipe2[0]);
        close(pipe2[1]);
        close(input_file);
        exit(0);
    }

    if (fork() == 0) {
        if (dup2(pipe1[0], STDIN_FILENO) == -1) {
            perror("Chyba při duplikování pipe1[0] na STDIN_FILENO");
            exit(1);
        }
        if (dup2(pipe2[1], STDOUT_FILENO) == -1) {
            perror("Chyba při duplikování pipe2[1] na STDOUT_FILENO");
            exit(1);
        }

        close(pipe1[0]);
        close(pipe1[1]);
        close(pipe2[0]);
        close(pipe2[1]);

        execlp("sort", "sort", NULL);
        perror("Chyba při spouštění sort");
        exit(1);
    }

    if (fork() == 0) {
        if (dup2(pipe2[0], STDIN_FILENO) == -1) {
            perror("Chyba při duplikování pipe2[0] na STDIN_FILENO");
            exit(1);
        }

        close(pipe1[0]);
        close(pipe1[1]);
        close(pipe2[0]);
        close(pipe2[1]);

        std::string grep_command = "[^";
        grep_command += ignored_char;
        grep_command += "]";

        execlp("grep", "grep", "-i", "-v", grep_command.c_str(), NULL);
        perror("Chyba při spouštění grep");
        exit(1);
    }

    if (fork() == 0) {
        if (dup2(pipe2[0], STDIN_FILENO) == -1) {
            perror("Chyba při duplikování pipe2[0] na STDIN_FILENO");
            exit(1);
        }

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

    fprintf(stderr, "Pocet predanych bajtu: %d\n", out_bytes);
    return 0;
}