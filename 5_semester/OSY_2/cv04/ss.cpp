#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>

#define MAX_NAMES 1000
#define MAX_NAME_LENGTH 100

typedef struct {
    char names[MAX_NAMES][MAX_NAME_LENGTH];
    int count;
} NameList;

int load_names(const char *filename, NameList *list) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        perror("Chyba při otevírání souboru");
        return -1;
    }

    list->count = 0;
    while (fgets(list->names[list->count], MAX_NAME_LENGTH, f) != NULL) {
        size_t len = strlen(list->names[list->count]);
        if (len > 0 && list->names[list->count][len - 1] == '\n')
            list->names[list->count][len - 1] = '\0';
        list->count++;
        if (list->count >= MAX_NAMES) break;
    }

    fclose(f);
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Použití: %s <soubor_se_jmeny> <N>\n", argv[0]);
        return 1;
    }

    int N = atoi(argv[2]);
    if (N <= 0) {
        fprintf(stderr, "N musí být kladné číslo\n");
        return 1;
    }

    NameList names;
    if (load_names(argv[1], &names) == -1 || names.count == 0) {
        fprintf(stderr, "Soubor se jmény nelze načíst nebo je prázdný.\n");
        return 1;
    }

    srand(time(NULL));

    int p1[2], p2[2], p3[2];
    if (pipe(p1) == -1 || pipe(p2) == -1 || pipe(p3) == -1) {
        perror("pipe");
        return 1;
    }

    pid_t pid1 = fork();
    if (pid1 == 0) {
        close(p1[0]);
        close(p2[0]); close(p2[1]);
        close(p3[0]); close(p3[1]);
        int x = ( getpid() % 100 ) + 10;
        for (int line_num = 1; line_num <= x; line_num++) {
            int idx = rand() % names.count;
            dprintf(p1[1], "%d. %s (%d)\n", line_num, names.names[idx], getpid());
            usleep(100000);
        }

        close(p1[1]);
        exit(0);
    }

    pid_t pid2 = fork();
    if (pid2 == 0) {
        close(p1[1]);
        close(p2[0]);
        close(p3[0]);

        FILE *fp = fdopen(p1[0], "r");
        char line[512];
        
        while (fgets(line, sizeof(line), fp) != NULL) {
            int num, pid_val;
            char name[MAX_NAME_LENGTH];
            
            if (sscanf(line, "%d. %s (%d)", &num, name, &pid_val) == 3) {
                int name_len = strlen(name);
                
                if (name_len <= N) {
                    dprintf(p2[1], "%d. %s (%d)(%d)\n", num, name, pid_val, getpid());
                } else {
                    dprintf(p3[1], "%d. %s (%d)(%d)\n", num, name, pid_val, getpid());
                }
            }
        }

        fclose(fp);
        close(p2[1]);
        close(p3[1]);
        exit(0);
    }

    pid_t pid3 = fork();
    if (pid3 == 0) {
        close(p1[0]); close(p1[1]);
        close(p2[1]);
        close(p3[0]); close(p3[1]);

        FILE *fp = fdopen(p2[0], "r");
        char line[512];
        
        while (fgets(line, sizeof(line), fp) != NULL) {
            int num, pid1_val, pid2_val;
            char name[MAX_NAME_LENGTH];
            
            if (sscanf(line, "%d. %s (%d)(%d)", &num, name, &pid1_val, &pid2_val) == 4) {
                printf("%3d. %10s (%7d)(%7d)(%7d) |\n", num, name, pid1_val, pid2_val, getpid());
                fflush(stdout);
            }
        }

        fclose(fp);
        exit(0);
    }

    pid_t pid4 = fork();
    if (pid4 == 0) {
        close(p1[0]); close(p1[1]);
        close(p2[0]); close(p2[1]);
        close(p3[1]);

        FILE *fp = fdopen(p3[0], "r");
        char line[512];
        
        while (fgets(line, sizeof(line), fp) != NULL) {
            int num, pid1_val, pid2_val;
            char name[MAX_NAME_LENGTH];
            
            if (sscanf(line, "%d. %s (%d)(%d)", &num, name, &pid1_val, &pid2_val) == 4) {
                printf("                                            | %3d. %10s (%7d)(%7d)(%7d)\n", num, name, pid1_val, pid2_val, getpid());
                fflush(stdout);
            }
        }

        fclose(fp);
        exit(0);
    }


    close(p1[0]); close(p1[1]);
    close(p2[0]); close(p2[1]);
    close(p3[0]); close(p3[1]);

    for (int i = 0; i < 4; i++) {
        wait(NULL);
    }
    
    return 0;
}