#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vernum_lib.h"

int verify_sum(const char* line)
{
    printf("DECIMAL_LIB: ");
    
    double sum = 0;
    double expected_sum;
    
    char* line_copy = strdup(line);
    char* part = strtok(line_copy, " ");
    
    while (part != NULL) {
        double number = atoi(part);
        part = strtok(NULL, " ");
        
        if (part != NULL) {
            sum += number;
        } else {
            expected_sum = number;
        }
    }
    
    free(line_copy);
    printf("Sum: %f, Expected sum: %f ", sum, expected_sum);
    return (sum == expected_sum) ? 1 : 0;
}