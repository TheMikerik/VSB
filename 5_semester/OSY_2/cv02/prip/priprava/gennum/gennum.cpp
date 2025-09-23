//***************************************************************************
//
// Program example for subject Operating Systems
//
// Petr Olivka, Dept. of Computer Science, petr.olivka@vsb.cz, 2021
//
// Program gennum M N - generates random numbers
// -f flag for decimal numbers
//
//***************************************************************************

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Header file for library
#include "gennum_lib.h"

int main(int argc, char* argv[]) {
    if (argc < 3 || argc > 4) {
        printf("!! %s M N [-f]\n", argv[0]);
        return 1;
    }
    
    int M = atoi(argv[1]);
    int N = atoi(argv[2]);
    int use_decimal = 0;
    
    if (argc == 4) {
        if (strcmp(argv[3], "-f") == 0) {
            use_decimal = 1;
        }
    }
    
    srand(time(NULL));
    
    for (int line = 0; line < N; line++) {
        if (use_decimal) {
            generate_random_decimal_line(M);
        } else {
          generate_random_whole_line(M);
        }
    }
    
    return 0;
}