#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pthread.h>
#include <unistd.h>

#define NUM_OF_BUYERS 20

pthread_mutex_t car1;
pthread_mutex_t car2;
pthread_mutex_t car3;
pthread_mutex_t car4;
pthread_mutex_t car5;

void* buyer(void* index) {

}

int main() {
    if (pthread_mutex_init(&car1, NULL) != 0) {
        perror("pthread_mutex_init");
        return 1;
    }

    if (pthread_mutex_init(&car2, NULL) != 0) {
        perror("pthread_mutex_init");
        return 1;
    }

    if (pthread_mutex_init(&car3, NULL) != 0) {
        perror("pthread_mutex_init");
        return 1;
    }

    if (pthread_mutex_init(&car4, NULL) != 0) {
        perror("pthread_mutex_init");
        return 1;
    }

    if (pthread_mutex_init(&car5, NULL) != 0) {
        perror("pthread_mutex_init");
        return 1;
    }

    pthread_t buyers[NUM_OF_BUYERS];

    for (long i = 0; i < NUM_OF_BUYERS; i++){
        if (pthread_create(&buyers[i], NULL, buyer, (void *)(i+1)) == -1){
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