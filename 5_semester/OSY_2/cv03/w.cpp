#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <fcntl.h>

struct mystat {
    char name[256];
    struct stat statbuf;
};

void vypis_prava(mode_t mode) {
    char p[10];
    p[0] = (mode & S_IRUSR) ? 'r' : '-';
    p[1] = (mode & S_IWUSR) ? 'w' : '-';
    p[2] = (mode & S_IXUSR) ? 'x' : '-';
    p[3] = (mode & S_IRGRP) ? 'r' : '-';
    p[4] = (mode & S_IWGRP) ? 'w' : '-';
    p[5] = (mode & S_IXGRP) ? 'x' : '-';
    p[6] = (mode & S_IROTH) ? 'r' : '-';
    p[7] = (mode & S_IWOTH) ? 'w' : '-';
    p[8] = (mode & S_IXOTH) ? 'x' : '-';
    p[9] = '\0';

    printf("%-9s ", p);
}

int cmp_size(const void *a, const void *b){
    const struct mystat *fa = (const struct mystat *)a;
    const struct mystat *fb = (const struct mystat *)b;

    return (fb->statbuf.st_size - fa->statbuf.st_size);
}

void vypis_obsah_souboru(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Nelze otevřít soubor pro čtení\n");
        return;
    }

    char buffer[1024];
    int line_count = 0;
    char **first_lines = (char **)malloc(5 * sizeof(char*));
    
    for (int i = 0; i < 5; i++) {
        if (!fgets(buffer, sizeof(buffer), file)) {
            break;
        }
        first_lines[i] = (char *)malloc(strlen(buffer) + 1);
        strcpy(first_lines[i], buffer);
        line_count++;
    }

    for (int i = 0; i < line_count; i++) {
        printf("%s", first_lines[i]);
        free(first_lines[i]);
    }
    
    free(first_lines);

    if (line_count < 5 || feof(file)) {
        fclose(file);
        return;
    }

    long current_pos = ftell(file);
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    
    if (file_size <= current_pos) {
        fclose(file);
        return;
    }

    int lines_from_end = 0;
    long pos = file_size - 2;
    char ch;

    while (pos >= current_pos && lines_from_end < 5) {
        fseek(file, pos, SEEK_SET);
        ch = fgetc(file);
        
        if (ch == '\n') {
            lines_from_end++;
            if (lines_from_end == 5) {
                pos = ftell(file);
                break;
            }
        }
        pos--;
    }

    if (lines_from_end < 5) {
        fseek(file, current_pos, SEEK_SET);
    } else {
        fseek(file, pos, SEEK_SET);
    }

    printf("...\n");

    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Použití: %s [přepínače] soubory...\n", argv[0]);
        return 1;
    }

    struct mystat seznam[argc];
    int count = 0;

    for (int i = 1; i < argc; i++) {
        struct stat st;

        if (stat(argv[i], &st) != 0) {
            fprintf(stderr, "Nelze získat informace o souboru: %s\n", argv[i]);
            continue;
        }

        if ((st.st_mode & S_IXUSR) || S_ISDIR(st.st_mode)) {
            continue;
        }

        if (access(argv[i], R_OK) != 0) {
            continue;
        }

        strncpy(seznam[count].name, argv[i], sizeof(seznam[count].name) - 1);
        seznam[count].name[sizeof(seznam[count].name) - 1] = '\0';
        seznam[count].statbuf = st;

        count++;
    }

    qsort(seznam, count, sizeof(struct mystat), cmp_size);

    for (int i = 0; i < count; i++){
        struct mystat *f = &seznam[i];

        vypis_prava(f->statbuf.st_mode);
        printf("%10ld ", (long)f->statbuf.st_size);

        char timebuf[100];
        struct tm *tm_info = localtime(&f->statbuf.st_mtime);
        strftime(timebuf,sizeof(timebuf),"%Y-%m-%d %H:%M:%S", tm_info);
        printf("%s ", timebuf);

        printf("%s\n", f->name);
        
        printf("---------------\n");
        vypis_obsah_souboru(f->name);
        printf("---------------\n");
    }

    return 0;
}