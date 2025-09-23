#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int vahy[] = { 1, 2, 4, 8, 5, 10, 9, 7, 3, 6 };

int main(int argc, char* argv[]) {
  bool binary = false;
  for (int i = 1; i < argc; i++) {
      if (strcmp(argv[i], "-b") == 0) {
          binary = true;
          break;
      }
  }

  long S = atol(argv[1]);
  long N = 1000;
  
  for (int i = 2; i < argc; i++) {
      if (strcmp(argv[i], "-b") != 0) {
          N = atol(argv[i]);
          break;
      }
  }

  long current = S;
  
  for (long i = 0; i < N; i++) {
      while (1) {
          char digits[11];
          snprintf(digits, sizeof(digits), "%010ld", current);
          
          int sum = 0;
          for (int j = 0; j < 10; j++) {
              sum += (digits[j] - '0') * vahy[j];
          }
          
          if (sum % 11 == 0) break;
          current++;
      }
      
      if (binary) {
          fwrite(&current, sizeof(long), 1, stdout);
      } else {
          char buffer[12];
          snprintf(buffer, sizeof(buffer), "%010ld\n", current);
          fwrite(buffer, sizeof(char), 11, stdout);
      }
      
      current++;
  }
  
  return 0;
}