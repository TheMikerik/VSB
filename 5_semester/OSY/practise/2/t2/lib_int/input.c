// File: project/lib_int/input.c
#include "input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void input(int L, int N, int is_float) {
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    for(int i = 0; i < L; i++) {
        if ((read = getline(&line, &len, stdin)) == -1) {
            fprintf(stderr, "Error reading line %d\n", i+1);
            break;
        }

        int index = 0, pos = 0, num;
        int sum = 0;
        int count = 0;

        while(index < read && count < N) {
            if(sscanf(line + index, "%d%c%n", &num, &pos, &pos) < 1) {
                break;
            }
            index += pos;
            sum += num;
            count++;
        }

        printf("Sum of line %d: %d\n", i+1, sum);
    }

    free(line);
}

//cd project/lib_int
// gcc -fPIC -c input.c -o input.o
// gcc -shared -o libinput.so input.o