#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "output.h"

void output(int t_L, int t_N, int is_float);

int main(int argc, char *argv[]) {
    if (argc < 3 || argc > 4) {
        printf("Použití: %s [-f] <L> <N>\n", argv[0]);
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

    output(L, N, is_float);

    return 0;
}
