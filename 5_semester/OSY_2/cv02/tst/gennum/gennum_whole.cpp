#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "gennum_lib.h"

int generate_random_number2() {
    int min = 10;
    int max = 9999;
    return min + rand() % (max - min + 1);
}

void generate_random_whole_line(int max_numbers) {
    int num_count = 1 + rand() % max_numbers;
    
    int sum = 0;
    
    for (int i = 0; i < num_count; i++) {
        int number = generate_random_number2();
        sum += number;
        
        printf("%d", number);
        
        if (i < num_count - 1) {
            printf(" ");
        }
    }
    
    printf(" %d\n", sum);
}