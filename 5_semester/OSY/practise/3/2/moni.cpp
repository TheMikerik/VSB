#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <unistd.h>
#include <cstring>
#include <ctime>
#include <cerrno>
#include <sys/wait.h>

#define SIZE_THRESHOLD 128  // Minimal size change for detection (128 bytes)

// Function to print the current time
void print_time() {
    time_t now = time(nullptr);
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&now));
    std::cout << buffer << " ";
}

// Function to check if the file has read permissions
bool has_read_permission(const char* filename) {
    return access(filename, R_OK) == 0;  // Returns true if file can be read
}

// Function to monitor an individual file
void monitor_file(const char* filename) {
    if (strstr(filename, "X_0K")) {
        std::cout << "Skipping file: " << filename << std::endl;
        return;
    }

    std::ifstream file(filename);
    if (!file) {
        std::perror("ifstream");
        return;
    }

    struct stat file_stat;
    off_t last_size = 0;

    // Start reading from the end of the file, similar to `tail -f`
    file.seekg(0, std::ios::end);
    last_size = file.tellg();

    while (true) {
        // Check if file still has read permissions
        if (!has_read_permission(filename)) {
            std::cout << "Cannot read file: " << filename << " (Permission denied)" << std::endl;
            usleep(1000000);  // Delay before the next attempt
            continue;
        }

        if (stat(filename, &file_stat) == -1) {
            std::perror("stat");
            file.close();
            return;
        }

        off_t current_size = file_stat.st_size;

        if (current_size < last_size) {
            // File was truncated
            std::cout << "\nFile truncated at ";
            print_time();
            std::cout << "Filename: " << filename << std::endl;
            last_size = current_size;
            file.close();
            file.open(filename);
            file.seekg(0, std::ios::beg);
        }

        if (current_size - last_size >= SIZE_THRESHOLD) {
            // File grew by more than 128 bytes
            std::cout << "\nFile grew at ";
            print_time();
            std::cout << "Filename: " << filename << std::endl;
            std::cout << "Size increased by: " << current_size - last_size << " bytes\n";

            // Read new lines
            file.seekg(last_size, std::ios::beg);
            std::string line;
            while (std::getline(file, line)) {
                std::cout << line << std::endl;  // Print new lines
            }
            last_size = file.tellg();
        }

        usleep(1000000);  // Check for changes every 0.5 seconds
    }

    file.close();
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <filename1> <filename2> ... <filenameN>" << std::endl;
        return 1;
    }

    // For each file provided in the arguments, call monitor_file in a parallel process
    for (int i = 1; i < argc; ++i) {
        pid_t pid = fork();  // Use fork for parallel processing
        if (pid == 0) {
            monitor_file(argv[i]);
            exit(0);
        }
    }

    // Wait for all processes to finish
    while (wait(nullptr) > 0);

    return 0;
}
