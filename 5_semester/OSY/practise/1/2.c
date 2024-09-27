#include <stdio.h>

int main(int argc, char **argv) {
    int num, sum = 0;

    u_int8_t binary = 0;

    if(argc > 1 && strcmp(argv[1], "-b") == 0) {
      binary = 1;
    }

    int error = 0;

    while (1) {
      if(binary) {
        error = scanf("%d", &num);
        if(error == EOF) break;
      } else {
        error = fread(&num, sizeof(int), 1, stdin);
        if(error == 0) break;
      }

      sum += num;
    }
      printf("Sum: %d\n", sum);

    return 0;
}
