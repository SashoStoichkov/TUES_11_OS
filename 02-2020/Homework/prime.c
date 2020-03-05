#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>

#include "functions.h"

int is_prime(long number){
    int flag = 1;

    for (long i = 2; i < number / 2; i++){
        if (number % i == 0){
            flag = 0; break;
        }
    }

    return flag;
}

void *count_of_primes(void *number){
    printf("Prime calculation started for N=%ld\n", (long)number);
    int count = 0;

    for (long i = 2; i < (long)number; i++){
        if (is_prime(i) == 1){
            count++;
        }
    }

    if ((long)number >= 4){
        count--;
    }

    printf("Number of primes for N=%ld is %d\n", (long)number, count);
    pthread_exit((void *) 0);
}