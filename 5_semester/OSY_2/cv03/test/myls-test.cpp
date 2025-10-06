#include <iostream>
#include <sys/stat.h>
#include <ctime>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <unistd.h>

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
    if (access(file.c_str(), X_OK) != 0) {
        return true;
    }
    if (access(file.c_str(), R_OK) != 0) {
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
    
    
    printf("---------------\n");
    
    printf("...\n");

    
}

int main(int argc, char* argv[]) {
    std::vector<mystat> files;

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

    return 0;
}