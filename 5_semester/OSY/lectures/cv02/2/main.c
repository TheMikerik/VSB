#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"

void input(int t_L, int t_N);

int main(int argc, char *argv[]) {
    if (argc < 2 || argc >= 3) {
        printf("Spatny syntax pri spusteni");
        return 1;
    }

    int L, N;

    if (argc == 2 ) {
        L = atoi(argv[1]);
        N = atoi(argv[2]);
    }

    input(L, N);

    return 0;
}