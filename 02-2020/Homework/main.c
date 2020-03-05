//------------------------------------------------------------------------------
// NAME: Александър Стоичков
// CLASS: XIb
// NUMBER: 2
// PROBLEM: Primes
// FILE NAME: main.c
// FILE PURPOSE:
// Да се реализира програма, която изчислява броя на простите числа от 2 до N.
//------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pthread.h>
#define NUM_THREADS 100

#include "functions.h"

int main(int argc, char const *argv[]){
    int num_of_actual_threads = 0;
    pthread_t threads[NUM_THREADS];

    do {
        char input[10000];
        long number;

        fgets(input, 10000, stdin);

        if (input[0] == 'e' && strlen(input) == 2){ // 2 = 'e' + '\n'
            break;
        } else if (input[0] == 'p' && input[1] == ' '){
            int is_number = 1;
            char number_string[strlen(input)];

            for (int i = 2, j = 0; i < strlen(input)-1; i++, j++){
                if (input[i] >= '0' && input[i] <= '9'){
                    number_string[j] = input[i];
                } else {
                    printf("Supported commands:\n");
                    printf("p N - Starts a new calculation for the number of primes from 1 to N\n");
                    printf("e - Waits for all calculations to finish and exits\n");
                    is_number = 0; break;
                }
            }

            if (is_number){
                number = atol(number_string);

                if (pthread_create(&threads[num_of_actual_threads++], NULL, count_of_primes, (void *)number) == -1){
                    perror("pthread_create");
                    return 1;
                }
            }
        } else {
            printf("Supported commands:\n");
            printf("p N - Starts a new calculation for the number of primes from 1 to N\n");
            printf("e - Waits for all calculations to finish and exits\n");
        }

    } while (num_of_actual_threads < NUM_THREADS);

    pthread_exit(NULL);
    return 0;
}
