// input_hex/input.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void input(int t_L, int t_N) {
    char line[1024];
    for (int i = 0; i < t_L; i++) {
        char sign;
        unsigned int num;
        int offset = 0;
        for (int j = 0; j < t_N; j++) {
            int buffer;
            if( sscanf(line + offset, " %c0x%X%c%n", &sign, &num, &sign, &buffer) == 2 ){
                printf("%c0x%X%c", sign, num, sign);
                offset += buffer;
            }
        }
    }
}