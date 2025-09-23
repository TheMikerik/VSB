#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "gennum_lib.h"

int generate_random_number() {
    int min = 10;
    int max = 9999;
    return min + rand() % (max - min + 1);
}

void generate_random_decimal_line(int max_numbers) {
    int num_count = 1 + rand() % max_numbers;
    
    int sum = 0;
    
    for (int i = 0; i < num_count; i++) {
        int number = generate_random_number();
        sum += number;
        
        printf("%d.00", number);
        
        if (i < num_count - 1) {
            printf(" ");
        }
    }
    
    printf(" %d.00\n", sum);
}