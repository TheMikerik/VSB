#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "output.h"

void output(int t_L, int t_N) {

    for (int i = 0; i < t_L; i++) {
        int sum = 0;
        for (int j = 0; j < t_N; j++) {
            int num = (rand() % 2001) - 1000; 
            printf("%d ", num);
            sum += num;
        }

        printf("%d\n", sum);
    }
}
