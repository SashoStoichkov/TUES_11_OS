//------------------------------------------------------------------------------
// NAME: Александър Стоичков
// CLASS: XIb
// NUMBER: 2
// PROBLEM: Miners
// FILE NAME: main.c
// FILE PURPOSE:
// Целта на задачата е да се реализира синхронизация на нишки посредством mutex.
//------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pthread.h>
#include <unistd.h>

int gold = 0;
pthread_mutex_t lock;

void *trader(void *index){
    pthread_mutex_lock(&lock);

    if (gold - 10 < 0){
        printf("The warehouse is empty, cannot sell!\n");
    } else {
        gold -= 10;
        printf("Trader %ld sold 10 gold\n", (long)index);
    }

    sleep(2);

    pthread_mutex_unlock(&lock);
    return NULL;
}

void *miner(void *index){
    pthread_mutex_lock(&lock);

    gold += 10;

    printf("Miner %ld gathered 10 gold\n", (long)index);

    sleep(2);

    pthread_mutex_unlock(&lock);
    return NULL;
}

int main(int argc, char const *argv[]){
    int num_of_miners, num_of_traders;

    if (argc == 1){
        num_of_miners = 1;
        num_of_traders = 1;
    } else if (argc == 3){
        num_of_miners = atoi(argv[1]);
        num_of_traders = atoi(argv[2]);
    }

    pthread_t miners[num_of_miners];
    pthread_t traders[num_of_traders];

    if (pthread_mutex_init(&lock, NULL) != 0){
        perror("pthread_mutex_init");
        return 1;
    }

    for (int j = 0; j < 20; j++){
        for (long i = 0; i < num_of_miners; i++){
            if (pthread_create(&miners[i], NULL, miner, (void *)(i+1)) == -1){
                perror("pthread_create");
                return 2;
            }
        }

        for (int i = 0; i < num_of_miners; i++){
            if (pthread_join(miners[i], NULL) == -1){
                perror("pthread_join");
                return 3;
            }
        }
    }


    for (int j = 0; j < 20; j++){
        for (long i = 0; i < num_of_traders; i++){
            if (pthread_create(&traders[i], NULL, trader, (void *)(i+1)) == -1){
                perror("pthread_create");
                return 2;
            }
        }

        for (int i = 0; i < num_of_traders; i++){
            if (pthread_join(traders[i], NULL) == -1){
                perror("pthread_join");
                return 3;
            }
        }
    }

    pthread_mutex_destroy(&lock);
    printf("Gold: %d\n", gold);

    return 0;
}
