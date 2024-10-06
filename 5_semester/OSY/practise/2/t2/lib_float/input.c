// File: project/lib_float/input.c
#include "input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void input(int L, int N, int is_float) {
    // is_float is handled implicitly by using float parsing
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    for(int i = 0; i < L; i++) {
        if ((read = getline(&line, &len, stdin)) == -1) {
            fprintf(stderr, "Error reading line %d\n", i+1);
            break;
        }

        int index = 0, pos = 0;
        float num;
        float sum = 0.0f;
        int count = 0;

        while(index < read && count < N) {
            if(sscanf(line + index, "%f%c%n", &num, &pos, &pos) < 1) {
                break;
            }
            index += pos;
            sum += num;
            count++;
        }

        printf("Sum of line %d: %.2f\n", i+1, sum);
    }

    free(line);
}





// cd project/lib_float
// gcc -fPIC -c input.c -o input.o
// gcc -shared -o libinput.so input.o