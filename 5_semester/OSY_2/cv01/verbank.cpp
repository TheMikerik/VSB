#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int vahy[] = { 1, 2, 4, 8, 5, 10, 9, 7, 3, 6 };

int main(int argc, char* argv[]) {
  bool binary = false;
  int print_valid = 0;
    
  for (int i = 1; i < argc; i++) {
      if (strcmp(argv[i], "-v") == 0) {
          print_valid = 1;
      }
      if (strcmp(argv[i], "-b") == 0) {
          binary = true;
      }
  }
  
  long cislo_uctu;
  
  while (
    binary
    ? fread(&cislo_uctu, sizeof(long), 1, stdin) == 1
    : scanf("%ld", &cislo_uctu) == 1
  ) {
      long temp = cislo_uctu;
      int sum = 0;
      
      for (int i = 0; i < 10; i++) {
          sum += (temp % 10) * vahy[i];
          temp /= 10;
      }
      
      int is_valid = (sum % 11) == 0;
      
      if (print_valid && !is_valid) {
          continue;
      }
      
      if (is_valid) {
       printf("%010ld platný\n", cislo_uctu);
      } else {
        printf("%010ld neplatný\n", cislo_uctu);
      }
  }
  
  return 0;
}