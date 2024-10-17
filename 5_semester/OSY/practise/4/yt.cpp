#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main () {
    int pipe1 [2];
    int pipe2 [2];
    int pipe3 [2];

    pipe (pipe1);
    pipe (pipe2);
    pipe (pipe3);

    if (fork () == 0) {
      close (pipe1 [0]);

      for (int i = 0; i < 10; i++) {
        char buffer [1024];
        sprintf (buffer, "Number: %d\n", rand () % 10000);
        write (pipe1 [1], buffer, strlen (buffer));
        usleep (500 * 1000);
      }

      close (pipe1 [1]);
      exit (0);
    }
    if (fork () == 0) {
      close (pipe1 [1]);

      char buffer[1024];
      while (read(pipe1[1], buffer, sizeof(buffer)) > 0) {
          printf("Received: %s\n", buffer);
      }
      close(pipe1[0]);
      exit(0);
    }
    wait (NULL);
    printf("PID: %d\n", getpid());
    printf("PPID: %d\n\n", getppid());
    close (pipe1 [0]);
    close (pipe1 [1]);
}