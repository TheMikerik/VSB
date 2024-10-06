#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "output.h"

void output(int t_L, int t_N, int is_float) {
    srand(time(NULL));

    for (int i = 0; i < t_L; i++) {
        double sum = 0.0;

        for (int j = 0; j < t_N; j++) {
            double num;
            
            if (is_float) {
                num = ((rand() % 2001) - 1000) / 100.0;
                printf("%s%.2f ", (num >= 0) ? "+" : "", num);
            } else {
                num = (rand() % 2001) - 1000;
                printf("%s%d ", (int)num >= 0 ? "+" : "", (int)num);
            }

            sum += num;
        }

        if (is_float) {
            printf("= %.2f\n", sum);
        } else {
            printf("= %d\n", (int)sum);
        }
    }
}