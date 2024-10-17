#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>

int main(int argc, char *argv[]){
  if (argc < 3) {
    printf("Spatne zadane parametry: %s <pocet cisel> <radky za minutu>\n", argv[0]);
    exit(1);
  };
  
  srand(time(NULL));

  int pipe1[2];
  int pipe2[2];
  int pipe3[2];
  if (pipe(pipe1) == -1 || pipe(pipe2) == -1 || pipe(pipe3) == -1) {
      perror("pipe");
      exit(EXIT_FAILURE);
  }

  if( fork() == 0 ) {
    close(pipe1[1]);
    close(pipe2[0]);
    close(pipe3[0]);
    close(pipe3[1]);

    int numbers, speed;
    char buffer[100];

    int l = read(pipe1[0], buffer, sizeof(buffer));

    if ( l > 0 ) {
      buffer[l] = '\0';
      sscanf(buffer, "%d %d", &numbers, &speed);
    }
    // printf("if exit\n");

    for (int i = 1; i < (numbers+1); i++) {
      // printf( "generace cisel\n" );

      int num = rand() % 1000;
      char b2[100];
      snprintf(b2, sizeof(b2), "%d. %d\n", i, num);
      write(pipe2[1], b2, strlen(b2));
      printf("1st child:\t %d. %d\n", i, num);
      usleep(1000000 / speed);
    }

    close(pipe1[0]);
    close(pipe2[1]);

    exit(0);
  }
  if(fork() == 0) {
    close(pipe1[0]);
    close(pipe1[1]);
    close(pipe2[1]);
    close(pipe3[0]);

    char buffer[100];
    int l;

    while( (l = read(pipe2[0], buffer, sizeof(buffer))) > 0 ) {
      buffer[l] = '\0';
      if(buffer[l-1] == '\n') buffer[l-1] = '\0';

      int generated_num;
      char operation;
      operation = (rand() % 2 == 0) ? '+' : '-';
      generated_num = rand() % 1000;

      char b2[100];
      snprintf(b2, sizeof(b2), "%s%c%d\n", buffer, operation, generated_num);
      write(pipe3[1], b2, strlen(b2));
      printf("2nd child:\t %s", b2);
    }


    close(pipe2[0]);
    close(pipe3[1]);

    exit(0);
  }
  if (fork() == 0){
    close(pipe1[0]);
    close(pipe1[1]);
    close(pipe2[0]);
    close(pipe2[1]);
    close(pipe3[1]);

    char buffer[100];
    int l;


    while ((l = read(pipe3[0], buffer, sizeof(buffer))) > 0) {
      buffer[l] = '\0';
      if(buffer[l-1] == '\n') buffer[l-1] = '\0';

      int row, num1, num2, result;
      char operation;
      sscanf(buffer, "%d. %d%c%d", &row, &num1, &operation, &num2);
      result = (operation == '+') ? (num1 + num2) : (num1 - num2);
      snprintf(buffer, sizeof(buffer), "%d. %d%c%d=%d\n", row, num1, operation, num2, result);
      printf("3rd child: \t %s\n", buffer);
    }

    close(pipe3[0]);
    exit(0);
  }

  close(pipe1[0]);
  close(pipe2[0]);
  close(pipe2[1]);
  close(pipe3[0]);
  close(pipe3[1]);


  int numbers = atoi(argv[1]);
  int speed = atoi(argv[2]);

  char buffer[100];
  snprintf(buffer, sizeof(buffer), "%d %d", numbers, speed);
  write(pipe1[1], buffer, strlen(buffer) + 1);
  close(pipe1[1]);

  wait(NULL);
  return 0;  
}