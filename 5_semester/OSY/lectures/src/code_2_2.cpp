#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
// #include <sys/>
#include <sys/stat.h>
#include <fcntl.h>

int main (int argn, char **argc) {
  int myPipe[ 2 ];
  pipe(myPipe);

  if (fork() == 0){
    dup2(myPipe[ 1 ], 1); // stdout
    close(myPipe[ 0 ]);
    close(myPipe[ 1 ]);
    execlp("ls", "ls", NULL);
    printf("This line will not be printed\n");
  }
  if (fork() == 0){
    close(myPipe[ 1 ]);
    dup2( myPipe[ 0 ], 0); // stdin
    close(myPipe[ 0 ]);
    int fd = open("out.ls", O_RDWR | O_CREATE, 0600);
    dup2(fd, 1);
    close(fd);
    execlp("nl", "nl", NULL);
    printf("This line will not be printed\n");
  }
  close(myPipe[ 1 ]);
  close(myPipe[ 0 ]);
  wait(NULL);

}
