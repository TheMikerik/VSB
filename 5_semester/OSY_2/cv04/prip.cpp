#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>


int main(int argc, char *argv[]) {
  if (argc != 2) exit(1);

  FILE *names = fopen(argv[1], "r");
  if (!names) {
    perror("File wont open");
    exit(1);
  }

  int pipe1[ 2 ];
  int pipe2[ 2 ];
  int pipe3[ 2 ];

  pipe(pipe1);
  pipe(pipe2);
  pipe(pipe3);

  if (fork() == 0){
    close(pipe1[ 0 ]);
    close(pipe2[ 1 ]);
    close(pipe2[ 0 ]);
    close(pipe3[ 1 ]);
    close(pipe3[ 0 ]);
    
    int lines_count = 0;
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), names) != NULL){
      lines_count++;
    }
    rewind(names);

    int generate_names_count = (getpid() % 100) + 10;
    srand(getpid());

    for (int i=0; i<generate_names_count; i++){
      int random_line = rand() % lines_count;
      rewind(names);

      int current_line = 0;
      while(fgets(buffer, sizeof(buffer), names) != NULL){
        if (current_line == random_line){
          buffer[strcspn(buffer, "\n")] = '\0';
          break;
        }
        current_line++;
      }

      write(pipe1[ 1 ], buffer, strlen(buffer) + 1);
      usleep(1000000 / 20);
    }


    close(pipe1[ 1 ]);
    exit(0);
  }
  if (fork() == 0){
    close(pipe1[ 1 ]);
    close(pipe2[ 0 ]);
    close(pipe3[ 1 ]);
    close(pipe3[ 0 ]);
    
    int line_count = 1;
    char buffer[256];
    
    while( read(pipe1[ 0 ], buffer, sizeof(buffer)) > 0 ){
      char output[512];
      sprintf(output, "%d: %s\n", line_count++, buffer);
      write(pipe2[ 1 ], output, strlen(output) + 1);
    }
    
    close(pipe2[ 1 ]);
    close(pipe1[ 0 ]);
    exit(0);
  }
  if (fork() == 0){
    close(pipe1[ 1 ]);
    close(pipe1[ 0 ]);
    close(pipe2[ 1 ]);
    close(pipe3[ 0 ]);

    char stream[512];
    while( read( pipe2[ 0 ], stream, sizeof(stream)) > 0){
      int line_num;
      char name[512];
      char output[512];

      sscanf(stream, "%d: %s", &line_num, name);

      sprintf(output, "%d: %s (%ld)\n", line_num, name, strlen(name) );
      write( pipe3[ 1 ], output, strlen(output) + 1);
    }


    close(pipe2[ 0 ]);
    close(pipe3[ 1 ]);
    exit(0);
  }

  close(pipe1[ 1 ]);
  close(pipe1[ 0 ]);
  close(pipe2[ 1 ]);
  close(pipe2[ 0 ]);
  close(pipe3[ 1 ]);

  char pipe_input[512];
  while( read( pipe3[ 0 ], pipe_input, sizeof(pipe_input)) > 0 ){
    int line;
    char name[256];
    int name_length;

    sscanf(pipe_input, "%d: %s (%d)", &line, name, &name_length);

    rewind(names);
    char file_buffer[256];
    int position = 1;
    bool found = false;

    while (fgets(file_buffer, sizeof(file_buffer), names) != NULL){
      file_buffer[strcspn(file_buffer, "\n")] = '\0';

      if (strcmp(file_buffer, name) == 0){
        found = true;
        break;
      }
      position++;
    }

    if (found){
      printf("%d: %s (%d) - %d\n", line, name, name_length, position);
    } else {
      printf("%d: %s (%d) - NOT FOUND\n", line, name, name_length);
    }
  }

  close(pipe3[ 0 ]);
  fclose(names);
  wait(NULL);
  wait(NULL);
  wait(NULL);

  return 0;
}