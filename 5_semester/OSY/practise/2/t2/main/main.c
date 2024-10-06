// File: project/main/main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"

int main(int argc, char *argv[]) {
    if (argc < 3 || argc > 4) {
        printf("Usage: %s [-f] <L> <N>\n", argv[0]);
        return 1;
    }

    int L, N, is_float = 0;

    if (argc == 4 && strcmp(argv[1], "-f") == 0) {
        is_float = 1;
        L = atoi(argv[2]);
        N = atoi(argv[3]);
    } else if (argc == 3) {
        L = atoi(argv[1]);
        N = atoi(argv[2]);
    }

    input(L, N, is_float);

    return 0;
}


// cd project/main
// gcc -o main main.c -ldl



// # Navigate to lib_int and compile
// cd project/lib_int
// gcc -fPIC -c input.c -o input.o
// gcc -shared -o libinput.so input.o

// # Navigate to lib_float and compile
// cd ../lib_float
// gcc -fPIC -c input.c -o input.o
// gcc -shared -o libinput.so input.o

// # Navigate to main and compile
// cd ../main
// gcc -o main main.c -ldl


// # Set LD_LIBRARY_PATH to lib_int
// export LD_LIBRARY_PATH=../lib_int:$LD_LIBRARY_PATH

// # Run the program without -f
// ./main 2 4




// # Set LD_LIBRARY_PATH to lib_float
// export LD_LIBRARY_PATH=../lib_float:$LD_LIBRARY_PATH

// # Run the program with -f
// ./main -f 2 4