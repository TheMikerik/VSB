#include <iostream>
#include <random>
#include <vector>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <ctime>

void output(int t_L, int t_N);

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

void output(int N, int L) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));


    int interval_ms = 60000 / L;

    // int radek = 0;
    while (true) {
        // std::cout << ++radek << ":";
        for (int j = 0; j < N; j++) {
            int num = std::rand() % 2001 - 1000;
            std::cout << ' ' << num << " ";
        }
        std::cout << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(interval_ms));
    }
}