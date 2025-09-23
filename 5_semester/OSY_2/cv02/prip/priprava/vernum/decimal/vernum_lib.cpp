//***************************************************************************
//
// Program example for subject Operating Systems
//
// Petr Olivka, Dept. of Computer Science, petr.olivka@vsb.cz, 2021
//
// Library for verification of whole numbers
//
//***************************************************************************

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../vernum_lib.h"

int verify_sum(const char* line)
{
    printf("Library: decimal numbers - File: %s Function: %s Line: %d\n", 
           __FILE__, __FUNCTION__, __LINE__);
    
    int count;
    double sum = 0.0, expected_sum;
    
    if (sscanf(line, "%d", &count) != 1) return -1;
    
    char* line_copy = strdup(line);
    char* token = strtok(line_copy, " ");
    token = strtok(NULL, " ");
    
    for (int i = 0; i < count && token != NULL; i++) {
        sum += atof(token);
        token = strtok(NULL, " ");
    }
    
    if (token != NULL) {
        expected_sum = atof(token);
    } else {
        free(line_copy);
        return -1;
    }
    
    free(line_copy);
    
    return (sum == expected_sum) ? 0 : 1;
}