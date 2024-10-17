#include <iostream>
#include <sys/stat.h>
#include <ctime>
#include <iomanip>
#include <vector>
#include <algorithm>

void printFileInfo(const std::string& file, bool showSize, bool showTime, bool showRights) {
    struct stat fileInfo;
    
    if (stat(file.c_str(), &fileInfo) != 0) {
        printf("File not found: %s\n", file.c_str());
        return;
    }

    if (showSize) printf("%12ld\t", (long)fileInfo.st_size);
    if (showTime) {
        printf("%.24s\t ", asctime(localtime(&fileInfo.st_ctime)));
    }
    if (showRights) {
        printf("%c%c%c%c%c%c%c%c%c\t",
            (fileInfo.st_mode & S_IRUSR) ? 'r' : '-',
            (fileInfo.st_mode & S_IWUSR) ? 'w' : '-',
            (fileInfo.st_mode & S_IXUSR) ? 'x' : '-',
            (fileInfo.st_mode & S_IRGRP) ? 'r' : '-',
            (fileInfo.st_mode & S_IWGRP) ? 'w' : '-',
            (fileInfo.st_mode & S_IXGRP) ? 'x' : '-',
            (fileInfo.st_mode & S_IROTH) ? 'r' : '-',
            (fileInfo.st_mode & S_IWOTH) ? 'w' : '-',
            (fileInfo.st_mode & S_IXOTH) ? 'x' : '-');
    }
    printf("%s\n", file.c_str());
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

    for (const auto& file : files) {
        printFileInfo(file, showSize, showTime, showRights);
    }

    return 0;
}