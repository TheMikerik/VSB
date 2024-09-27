#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h> 

int main(int argc, char *argv[]) {
  int count;
  count = atoi(argv[1]);

  int min, max;
  bool minmax = false;
  
  if (argc > 2) {
    min = atoi(argv[2]), max = atoi(argv[3]);
    minmax = true;
  }
  srand(time(NULL));

  int num;

  while (count > 0) {
    num = rand() % 100;
    if (minmax) {
      if (num >= min && num <= max) {
        printf("%d\n", num);
        count--;
      }
    } else {
      printf("%d\n", num);
      count--;
    }
  }
}