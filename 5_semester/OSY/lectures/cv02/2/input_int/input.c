// input_decimal/input.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void input(int t_L, int t_N) {
    char line[1024];
    for (int i = 0; i < t_L; i++) {
        int num;
        char opr;
        int offset = 0;
        for (int j = 0; j < t_N; j++) {
            int buffer;
            if ( sscanf(line + offset, " %d%c%n", &num, &opr, &buffer) == 2) {
                printf("%d%c", num, opr);
                offset += buffer;
                offset += buffer;
            }
        }
    }
}