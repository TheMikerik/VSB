#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main () {
    int my_pipe [2];

    if (fork () == 0) {

        close (my_pipe [1]); // important!!!

        while (1) {

            char buffer [333];
            int ret = read (my_pipe [0], buffer, sizeof (buffer));
            if (ret <= 0) break;
            write (1, buffer, ret);
        }
        exit (0);
    }
    
    if (fork () == 0) {

        close (my_pipe [0]);

        for (int i = 0; i < 10; i++) {

            char buffer [1024];
            sprintf (buffer, "Number: %d\n", rand () % 10000);
            write (my_pipe [1], buffer, strlen (buffer));
            usleep (500 * 1000);
        }
        close (my_pipe [1]);
    }
    close (my_pipe [0]);
    close (my_pipe [1]);

    wait (NULL);
    wait (NULL);
}