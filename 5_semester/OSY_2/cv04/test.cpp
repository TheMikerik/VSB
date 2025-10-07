#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>


int main(int argc, char *argv[]) {
  if (argc != 3) exit(1);

  FILE *names = fopen(argv[1], "r");
  if (!names) {
    perror("File wont open");
    exit(1);
  }

  int pipe1[ 2 ], pipe2[ 2 ], pipe3[ 2 ], pipe4[ 2 ];
  pipe(pipe1); pipe(pipe2); pipe(pipe3); pipe(pipe4);

  int lines_count = 0;
  char buffer[256];
  while (fgets(buffer, sizeof(buffer), names) != NULL){
    lines_count++;
  }

  if (fork() == 0){
    close(pipe1[ 1 ]);
    close(pipe2[ 0 ]);
    close(pipe3[ 0 ]); close(pipe3[ 1 ]);
    close(pipe4[ 0 ]); close(pipe4[ 1 ]);
    
    char p_buffer[256];
    while(read(pipe1[0], p_buffer, sizeof(p_buffer)) > 0){
      int selected_line;
      int pid1;

      sscanf(p_buffer, "%d (%d)", &selected_line, &pid1);

      char f_buffer[256];
      char output_buffer[256];
      int position = 0;

      rewind(names);
      while (fgets(f_buffer, sizeof(f_buffer), names) != NULL){
        if (selected_line == position){
          f_buffer[strcspn(f_buffer, "\n")] = '\0';
          sprintf(output_buffer, "%s (%d)(%d)", f_buffer, pid1, getpid());
          write(pipe2[1], output_buffer, strlen(output_buffer)+1);
        }
        position++;
      }
    }

    close(pipe1[ 0 ]);
    close(pipe2[ 1 ]);
    exit(0);
  }
  if (fork() == 0){
    close(pipe1[ 0 ]); close(pipe1[ 1 ]);
    close(pipe2[ 1 ]);
    close(pipe3[ 0 ]);
    close(pipe4[ 0 ]); close(pipe4[ 1 ]);
    
    char p_buffer[256];
    int line = 0;
    while( read(pipe2[0], p_buffer, sizeof(p_buffer)+1) > 0 ){
      char output_buffer[256];
      sprintf(output_buffer, "%d. %s(%d)", line++, p_buffer, getpid());
      write(pipe3[1], output_buffer, strlen(output_buffer)+1);
    }
    
    close(pipe2[ 0 ]);
    close(pipe3[ 1 ]);
    exit(0);
  }
  if (fork() == 0){
    close(pipe1[ 0 ]); close(pipe1[ 1 ]);
    close(pipe2[ 0 ]); close(pipe2[ 1 ]);
    close(pipe3[ 1 ]);
    close(pipe4[ 0 ]);
    
    char p_buffer[256];
    while( read(pipe3[0], p_buffer, sizeof(p_buffer)+1) > 0 ){
      char output_buffer[256];

      int line;
      char name[64];
      int pid1, pid2, pid3;

      sscanf(p_buffer, "%d. %s (%d)(%d)(%d)", &line, name, &pid1, &pid2, &pid3);
      
      if (strlen(name) < atoi(argv[2])){
        sprintf(output_buffer, "%s(%d)\t|", p_buffer, getpid());
        printf("%s\n", output_buffer);
      } else {
        sprintf(output_buffer, "%s(%d)", p_buffer, getpid());
        write( pipe4[1], output_buffer, strlen(output_buffer) + 1);
      }
    }

    
    close(pipe3[ 0 ]);
    close(pipe4[ 1 ]);
    exit(0);
  }
  if (fork() == 0){
    close(pipe1[ 0 ]); close(pipe1[ 1 ]);
    close(pipe2[ 0 ]); close(pipe2[ 1 ]);
    close(pipe3[ 1 ]);
    close(pipe4[ 1 ]);

    char p_buffer[256];
    while ( read(pipe4[0], p_buffer, sizeof(p_buffer)+1) > 0){
      char output_buffer[256];

      
      for (int i=0; i<5; i++){
        printf("\t");
      }
      sprintf(output_buffer, "| %s(%d)\n", p_buffer, getpid());
      printf("%s", output_buffer);
    }

    close(pipe4[ 1 ]);
    exit(0);
  }

  int generator_length = (getpid() % 100) + 10;
  
  srand(getpid());
  for (int i=0; i<generator_length; i++){
    int random_number = rand() % lines_count;

    char num_buffer[256];
    sprintf(num_buffer, "%d (%d)", random_number, getpid());
    write(pipe1[1], num_buffer, strlen(num_buffer) + 1);
    usleep(1000000 / 20);
  }

  close(pipe1[ 0 ]); close(pipe1[ 1 ]);
  close(pipe2[ 0 ]); close(pipe2[ 1 ]);
  close(pipe3[ 0 ]); close(pipe3[ 1 ]);
  close(pipe4[ 0 ]); close(pipe4[ 1 ]);
  fclose(names);
  wait(NULL); wait(NULL); wait(NULL); wait(NULL);

  return 0;
}