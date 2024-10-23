#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

void my_awk() {
    char buffer[32];

    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        int len = strlen(buffer);
        if (buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0'; 
            len--;                   
        }
        printf("%02d %s\n", len, buffer);
    }
}

void my_nl() {
    char buffer[32];
    int line_number = 1;

    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        int len = strlen(buffer);
        if (buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0'; 
            len--;                    
        }
        printf("%d. %s\n", line_number++, buffer);
    }
}

int main(int argc, char *argv[]) {

  if (argc != 2) {
      printf("Invalid parameters: %s <grep_argument>\n", argv[0]);
      exit(1);
  }

  std::string grep_arg = argv[1];
  
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

      my_awk();

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
      dup2(pipe3[1], STDOUT_FILENO);

      close(pipe1[0]);
      close(pipe1[1]);
      close(pipe2[0]);
      close(pipe2[1]);
      close(pipe3[0]);
      close(pipe3[1]);

      execlp("grep", "grep", grep_arg.c_str(), NULL);
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

      my_nl();
      exit(1);
  }

  close(pipe1[0]);
  close(pipe1[1]);
  close(pipe2[0]);
  close(pipe2[1]);
  close(pipe3[0]);
  close(pipe3[1]);

  wait(NULL);
  wait(NULL);
  wait(NULL);
  wait(NULL);

  return 0;
}