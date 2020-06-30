#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pthread.h>
#include <unistd.h>

#define NUM_OF_BUYERS 20

pthread_mutex_t cars_mutex[5];
int cars[5] = {1, 1, 1, 1, 1}; // all cars are free

void* buyer(void* index) {

    for (int i = 0; i < 5; i++) {
        if (cars[i] == 1) {

            if (pthread_mutex_trylock(&cars_mutex[i]) == 0) {

                cars[i] = 0;
                printf("Buyer %ld takes car %d.\n", (long)index, i);

                if (pthread_mutex_unlock(&cars_mutex[i]) == -1) {
                    perror("pthread_mutex_unlock");
                }

                printf("Buyer %ld returns car %d.\n", (long)index, i);
                cars[i] = 1;

                return NULL;
            } else {
                printf("Locked\n");
            }
        }
    }

    return NULL;
}

int main() {
    for (int i = 0; i < 5; i++){
        if (pthread_mutex_init(&cars_mutex[i], NULL) != 0) {
            perror("pthread_mutex_init");
            return 1;
        }
    }

    pthread_t buyers[NUM_OF_BUYERS];

    for (long i = 0; i < NUM_OF_BUYERS; i++){
        if (pthread_create(&buyers[i], NULL, buyer, (void *)(i)) == -1){
            perror("pthread_create");
            return 2;
        }
    }

    for (int i = 0; i < NUM_OF_BUYERS; i++){
        if (pthread_join(buyers[i], NULL) == -1){
            perror("pthread_join");
            return 3;
        }
    }
}