#include <iostream>
#include <sys/stat.h>
#include <ctime>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <unistd.h>
#include <fstream>
#include <sys/stat.h>
#include <chrono>
#include <thread>

struct mystat {
    char name[256];
    struct stat fileInfo;
};

bool shouldFilterFile(const std::string& file, struct stat& fileInfo) {
    if (stat(file.c_str(), &fileInfo) != 0) {
        return true;
    }
    if (S_ISDIR(fileInfo.st_mode)) {
        return true;
    }
    if (fileInfo.st_mode & S_IXUSR) {
        return true;
    }
    return false;
}

void printFileInfo(const mystat& file) {

    printf("%c%c%c%c%c%c%c%c%c\t",
        (file.fileInfo.st_mode & S_IRUSR) ? 'r' : '-',
        (file.fileInfo.st_mode & S_IWUSR) ? 'w' : '-',
        (file.fileInfo.st_mode & S_IXUSR) ? 'x' : '-',
        (file.fileInfo.st_mode & S_IRGRP) ? 'r' : '-',
        (file.fileInfo.st_mode & S_IWGRP) ? 'w' : '-',
        (file.fileInfo.st_mode & S_IXGRP) ? 'x' : '-',
        (file.fileInfo.st_mode & S_IROTH) ? 'r' : '-',
        (file.fileInfo.st_mode & S_IWOTH) ? 'w' : '-',
        (file.fileInfo.st_mode & S_IXOTH) ? 'x' : '-');
    printf("%10ld\t", (long)file.fileInfo.st_size);
    printf("%.24s\t ", asctime(localtime(&file.fileInfo.st_ctime)));
    printf("%s\n", file.name);
}

off_t get_file_size(const std::string& filename) {
    struct stat st;
    if (stat(filename.c_str(), &st) == 0)
        return st.st_size;
    return -1;
}

std::string get_current_time() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    return std::ctime(&now_time);
}


void monitorFile(const mystat& fileInput) {
    std::ifstream file;
    std::string filename = fileInput.name;
    off_t last_size = get_file_size(filename);

    file.open(filename);

    if (!file.is_open()) {
        std::cerr << "Nelze otevřít soubor: " << filename << std::endl;
        exit(1);
    }

    file.seekg(0, std::ios::end);
    std::string line;

    while (true) {
        off_t current_size = get_file_size(filename);
        if (current_size != last_size) {
            std::cout << "ZMENA " << filename << ":\n";
            std::cout << "Velikost změněna z " << last_size << " na " << current_size << " bajtů.\n" << std::endl;

            if (current_size < last_size) {
                file.clear();
            }

            last_size = current_size;
        }

        while (std::getline(file, line)) {
            std::cout << line << std::endl;
        }
        
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main(int argc, char* argv[]) {
    std::vector<mystat> files;
    std::vector<std::thread> threads;

    for (int i = 1; i < argc; ++i) {
        struct stat fileInfo;
        std::string arg = argv[i];
        mystat file;
        strcpy(file.name, arg.c_str());

        if (shouldFilterFile(file.name, fileInfo)) {
            continue;
        } else {
            file.fileInfo = fileInfo;
        }
        files.push_back(file);
    }

    std::sort(files.begin(), files.end(), [](const mystat& a, const mystat& b) {
        return a.fileInfo.st_size < b.fileInfo.st_size;
    });
    
    for (const auto& file : files) {
        printFileInfo(file);
    }

    for (const auto& file : files) {
        threads.emplace_back(monitorFile, file);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    return 0;
}