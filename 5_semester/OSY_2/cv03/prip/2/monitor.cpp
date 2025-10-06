#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <sys/stat.h>
#include <ctime>

std::string get_current_time() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    return std::ctime(&now_time);
}

off_t get_file_size(const std::string& filename) {
    struct stat st;
    if (stat(filename.c_str(), &st) == 0)
        return st.st_size;
    return -1;
}

void monitor_file(const std::string& filename) {
    std::ifstream file;
    off_t last_size = get_file_size(filename);

    file.open(filename);

    file.seekg(0, std::ios::end);
    std::string line;

    while (true) {
        off_t current_size = get_file_size(filename);
        if (current_size != last_size) {
            std::cout << "Změna velikosti souboru:\n";
            std::cout << "Čas: " << get_current_time();
            std::cout << "Velikost změněna z " << last_size << " na " << current_size << " bajtů.\n" << std::endl;

            if (current_size < last_size) {
                file.clear();
            }

            last_size = current_size;
        }

        while (std::getline(file, line)) {
            std::cout << line << std::endl;
        }


    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Použití: " << argv[0] << " <soubor>\n";
        return 1;
    }

    monitor_file(argv[1]);
    return 0;
}
