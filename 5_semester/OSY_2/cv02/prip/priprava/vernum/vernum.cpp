#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vernum_lib.h"

int main()
{
    char line[1024];
    int line_number = 0;
    
    while (fgets(line, sizeof(line), stdin)) {
        line_number++;

        line[strcspn(line, "\n")] = 0;
        if (strlen(line) == 0) continue;
        
        int result = verify_sum(line);
        
        if (result == 1) {
            printf("Radek %d: OK\n", line_number);
        } else {
            printf("Radek %d: NOK\n", line_number);
        }
    }
    return 0;
}