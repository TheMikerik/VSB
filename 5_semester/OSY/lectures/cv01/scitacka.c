#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include <string.h>


int main(int argc, char *argv[]){
  int num;
  long count = 0;
  bool binary = false;

  if(argc > 1){
    binary = (strcmp(argv[1], "-b") == 0) ? true : false;
  }

  while (binary ? fread(&num, sizeof(int), 1, stdin) != 0 : scanf("%d", &num) != EOF) {
        count += num;
    }

    printf("Total count: %ld\n", count);
    return 0;
}
