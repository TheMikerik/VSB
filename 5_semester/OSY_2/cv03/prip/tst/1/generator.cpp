#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

void output(int N, int L) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    int interval_us = 60000000 / L;
    int radek = 0;

    while (true) {
        printf("%d:", ++radek);
        for (int j = 0; j < N; j++) {
            int num = std::rand() % 2001 - 1000;
            printf(" %d", num);
        }
        printf("\n");
        fflush(stdout);
        usleep(interval_us);
    }
}


int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cout << "Usage: " << argv[0] << " <L> <N>" << std::endl;
        return 1;
    }

    int N = std::stoi(argv[1]);
    int L = std::stoi(argv[2]);

    output(N, L);

    return 0;
}