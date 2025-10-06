#include <iostream>
#include <random>
#include <vector>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <ctime>
#include <stdlib.h>
#include <time.h>

int generate_random_number2() {
    int min = 10;
    int max = 9999;
    return min + rand() % (max - min + 1);
}

void output(int max_nums, int lines_per_minute) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    int interval_ms = 60000 / lines_per_minute;
    
    while (true) {
        int sum = 0;
        for (int i = 0; i < max_nums; i++) {
            int number = generate_random_number2();
            sum += number;
            
            printf("%d", number);
            
            if (i < max_nums - 1) {
                printf(" ");
            }
        }
        printf(" %d\n", sum);
        fflush(stdout);

        std::this_thread::sleep_for(std::chrono::milliseconds(interval_ms));
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cout << "Usage: " << argv[0] << " <max_num_per_line> <lines_per_minute>" << std::endl;
        return 1;
    }

    int max_nums = std::stoi(argv[1]);
    int lines_per_minute = std::stoi(argv[2]);

    output(max_nums, lines_per_minute);

    return 0;
}