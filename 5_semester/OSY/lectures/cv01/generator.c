#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include <time.h>
#include <string.h>


int main(int argc, char *argv[]) {

  int count, min, max;
  bool minmax = false;
  bool binary = false;

  count = atoi(argv[1]);
  if (argc > 2) {
    binary = (strcmp(argv[2], "-b") == 0) ? true : false;
    min = atoi(argv[3]), max = atoi(argv[4]);
    minmax = true;
  }

  // srand(time(NULL));

  while(count > 0){
    if(minmax) {
      int num = rand() % (max - min + 1) + min;

      if(binary) {
        fwrite(&num, sizeof(int), 1, stdout);
      } else {
        printf("%d\n", num);
      }
      count--;
    } else {
      int num = rand() % 100;

      if (binary) {
        fwrite(&num, sizeof(int), 1, stdout);
      } else {
        printf("%d\n", num);
      }
      count--;
    }
  }

  return 0;
}