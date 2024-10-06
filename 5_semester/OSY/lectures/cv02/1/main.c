#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "output.h"

void output(int t_L, int t_N, int is_hex);

int main(int argc, char *argv[]) {
    if (argc < 3 || argc > 4) {
        printf("Spatny syntax pri spusteni");
        return 1;
    }

    int L, N, is_hex = 0;

    if (argc == 4 && strcmp(argv[1], "-x") == 0) {
        is_hex = 1;
        L = atoi(argv[2]);
        N = atoi(argv[3]);
    } else if (argc == 3) {
        L = atoi(argv[1]);
        N = atoi(argv[2]);
    }

    output(L, N, is_hex);

    return 0;
}