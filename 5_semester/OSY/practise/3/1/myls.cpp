#include <iostream>
#include <sys/stat.h>
#include <ctime>
#include <iomanip>
#include <vector>
#include <algorithm>

void printFileInfo(const std::string& file, bool showSize, bool showTime, bool showRights) {
    struct stat fileInfo;
    if (stat(file.c_str(), &fileInfo) != 0) {
        std::cout << "File not found: " << file << std::endl;
        return;
    }

    if (showSize) std::cout << std::setw(12) << fileInfo.st_size << "   ";
    if (showTime) std::cout << std::setw(10) << std::put_time(std::localtime(&fileInfo.st_ctime), "%Y-%m-%d %H:%M:%S") << "   ";
    if (showRights) std::cout << std::setw(10) << std::oct << fileInfo.st_mode << "   ";
    std::cout << file << std::endl;
}

int main(int argc, char* argv[]) {
    bool showSize = false, showTime = false, showRights = false;
    std::vector<std::string> files;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-s") showSize = true;
        else if (arg == "-t") showTime = true;
        else if (arg == "-r") showRights = true;
        else files.push_back(arg);
    }

    std::sort(files.begin(), files.end());

    for (const auto& file : files) {
        printFileInfo(file, showSize, showTime, showRights);
    }

    return 0;
}