#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <vector>
#include <unistd.h>
#include <sys/stat.h>
#include <ctime>
#include <filesystem>

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

bool is_monitorable(const std::string& filename) {
    if (access(filename.c_str(), X_OK) != 0) {
        if (access(filename.c_str(), W_OK) == 0) {
            return true;
        }
    }
    return false;
}

void monitor_file(const std::string& filename, int interval_ms) {
    std::ifstream file(filename);
    printf("Soubor otevren: %s\n", 
    off_t last_size = get_file_size(filename);

    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(interval_ms));
        
        off_t current_size = get_file_size(filename);
        if (current_size != last_size) {
            printf("\n\n--------------------------------\n");
            printf("%s\n", get_current_time().c_str());
            printf("%lld  %s\n", current_size, filename.c_str());
            printf("--------------------------------\n");

            if (current_size < last_size) {
                printf("Soubor %s byl zkracen.\n", filename.c_str());
                file.clear();
                file.seekg(0);
            } else {
                file.clear();
                file.seekg(last_size, std::ios::beg);
                
                std::string new_data;
                while (std::getline(file, new_data)) {
                    printf("\t%s\n", new_data.c_str());
                }
            }
            last_size = current_size;
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Spatne pouziti argumentu");
        return 1;
    }

    int interval_ms = std::stoi(argv[1]);
    std::vector<std::thread> threads;

    for (int i = 2; i < argc; ++i) {
        if (is_monitorable(argv[i])) {
            threads.emplace_back(monitor_file, argv[i], interval_ms);
        } else {
            printf("Soubor ignorovan: %s\n", argv[i]);
        }
    }

    for (auto& thread : threads) {
        thread.join();
    }

    return 0;
}
