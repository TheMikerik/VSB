#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>
#include <errno.h>

void print_time() {
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    char buf[32];
    
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", tm_info);
    printf("[%s] ", buf);
}

typedef struct {
    char *filename;
    int fd;
    off_t last_size;
} file_info;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Použití: %s soubor1 [soubor2 ...]\n", argv[0]);
        return 1;
    }

    int file_count = argc - 1;
    file_info *files = (file_info *)malloc(file_count * sizeof(file_info));

    if (!files) {
        perror("Chyba alokace paměti");
        return 1;
    }

    for (int i = 0; i < file_count; i++) {
        files[i].filename = argv[i + 1];
        files[i].fd = open(files[i].filename, O_RDONLY);

        if (files[i].fd < 0) {
            fprintf(stderr, "Nelze otevřít soubor %s: ", files[i].filename);

            perror("");

            for (int j = 0; j < i; j++) {
                close(files[j].fd);
            }

            free(files);
            return 1;
        }

        struct stat st;

        if (fstat(files[i].fd, &st) < 0) {
            fprintf(stderr, "fstat selhal pro %s: ", files[i].filename);

            perror("");

            close(files[i].fd);

            for (int j = 0; j < i; j++) {
                close(files[j].fd);
            }

            free(files);
            return 1;
        }

        files[i].last_size = st.st_size;
        printf("Monitoring souboru: %s (velikost: %ld bajtů)\n", 
               files[i].filename, (long)files[i].last_size);
    }

    char buffer[1024];

    while (1) {
        sleep(1);

        for (int i = 0; i < file_count; i++) {
            struct stat st;
            if (stat(files[i].filename, &st) < 0) {
                print_time();

                fprintf(stderr, "Chyba při čtení souboru %s: ", files[i].filename);
                perror("");

                continue;
            }

            if (st.st_size > files[i].last_size) {
                off_t diff = st.st_size - files[i].last_size;
                print_time();

                printf("Soubor %s zvětšen: %ld -> %ld (+%ld bajtů)\n",files[i].filename, (long)files[i].last_size, (long)st.st_size, (long)diff);

                lseek(files[i].fd, files[i].last_size, SEEK_SET);
                ssize_t bytes;

                while ((bytes = read(files[i].fd, buffer, sizeof(buffer))) > 0) {
                    fwrite(buffer, 1, bytes, stdout);
                }

                fflush(stdout);
                
                files[i].last_size = st.st_size;
            } else if (st.st_size < files[i].last_size) {
                print_time();

                printf("Soubor %s zkrácen: %ld -> %ld\n",files[i].filename, (long)files[i].last_size, (long)st.st_size);
                
                lseek(files[i].fd, 0, SEEK_SET);

                files[i].last_size = st.st_size;
            }
        }
    }

    for (int i = 0; i < file_count; i++) {
        close(files[i].fd);
    }
    free(files);
    
    return 0;
}