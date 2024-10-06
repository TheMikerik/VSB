#include <stdio.h>
#include <stdlib.h>

void output(int t_L, int t_N);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Použití: %s <L> <N>\n", argv[0]);
        return 1;
    }

    int L = atoi(argv[1]);
    int N = atoi(argv[2]);

    output(L, N);

    return 0;
}
