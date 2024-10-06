#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "output.h"

void output(int t_L, int t_N, int is_hex) {
    srand(time(NULL));

    for (int i = 0; i < t_L; i++) {
        for (int j = 0; j < t_N; j++) {
            int num = (rand() % 2001) - 1000;
            char sign = (num >= 0) ? '+' : '-';
            
            if (is_hex) {
                printf("%c0x%X", sign, abs(num));
                if (j == t_N - 1) {
                    printf("=");
                }
            } else {
                printf("%d%c", num, (j < t_N - 1) ? sign : '=');
            }
        }
        printf("\n");
    }
}