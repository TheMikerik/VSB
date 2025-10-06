#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vernum_lib.h"

int verify_sum(const char* line)
{
    printf("BINARY_LIB: ");
    
    int sum = 0;
    int expected_sum;
    
    char* line_copy = strdup(line);
    char* part = strtok(line_copy, " ");
    
    while (part != NULL) {
        int number = strtol(part, NULL, 8);
        part = strtok(NULL, " ");
        
        if (part != NULL) {
            sum += number;
        } else {
            expected_sum = number;
        }
    }
    
    free(line_copy);
    printf("Sum: %d, Expected sum: %d ", sum, expected_sum);
    return (sum == expected_sum) ? 1 : 0;
}