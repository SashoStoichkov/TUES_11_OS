//------------------------------------------------------------------------------
// NAME: Александър Стоичков
// CLASS: XIb
// NUMBER: 2
// PROBLEM: Zombie defense
// FILE NAME: main.c
// FILE PURPOSE:
// Целта на задачата е да се реализира проста игра с нишки.
//------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pthread.h>
#include <unistd.h>

#include "ui.h"

int GOLD = 100;
int HEALTH = 100;
int SOLDIER_COUNT = 0;
int ZOMBIE_DISTANCE = 5;
int ZOMBIE_COUNT = 1;
int MINER_COUNT = 0;

pthread_mutex_t lock;

void *zombie_attack() {
    while (1) {
        for (int i = 5; i >= 0; i--) {
            pthread_mutex_lock(&lock);
            print_zombies(i, ZOMBIE_COUNT);
            pthread_mutex_unlock(&lock);
            sleep(1);
        }

        if (ZOMBIE_COUNT > SOLDIER_COUNT) {
            pthread_mutex_lock(&lock);
            HEALTH -= (ZOMBIE_COUNT - SOLDIER_COUNT);
            pthread_mutex_unlock(&lock);

            print_fail("Zombie attack succeded ;(!");

            pthread_mutex_lock(&lock);
            if (HEALTH <= 0) {
                game_end(ZOMBIE_COUNT);
            } else {
                print_health(HEALTH);
            }
            pthread_mutex_unlock(&lock);
        } else {
            print_succ("Zombie attack deflected! :)");
        }

        pthread_mutex_lock(&lock);
        ZOMBIE_COUNT *= 2;
        pthread_mutex_unlock(&lock);
    }
}

void *miner() {
    while (1) {
        pthread_mutex_lock(&lock);
        GOLD += 10;
        pthread_mutex_unlock(&lock);

        pthread_mutex_lock(&lock);
        print_gold(GOLD);
        pthread_mutex_unlock(&lock);
        sleep(1);
    }

    return NULL;
}

void *soldier(int count) {
    pthread_mutex_lock(&lock);
    SOLDIER_COUNT += count;
    GOLD -= 10 * count;
    pthread_mutex_unlock(&lock);

    pthread_mutex_lock(&lock);
    print_gold(GOLD);
    print_soldiers(SOLDIER_COUNT);
    pthread_mutex_unlock(&lock);

    return NULL;
}

int main() {
    if (pthread_mutex_init(&lock, NULL) != 0) {
        perror("pthread_mutex_init");
        return 1;
    }

    init();

    pthread_mutex_lock(&lock);
    print_gold(GOLD);
    print_soldiers(SOLDIER_COUNT);
    print_zombies(ZOMBIE_DISTANCE, ZOMBIE_COUNT);
    print_health(HEALTH);
    pthread_mutex_unlock(&lock);

    pthread_t zombies;
    if (pthread_create(&zombies, NULL, zombie_attack, NULL) == -1) {
        perror("pthread_create");
        return 2;
    }

    while (1) {
        int ch = get_input();

        switch (ch){
            case 'm':
                if (GOLD - 100 >= 0) {
                    print_msg("Miner created!");

                    pthread_t miners;
                    if (pthread_create(&miners, NULL, miner, NULL) == -1) {
                        perror("pthread_create");
                        return 2;
                    }

                    pthread_mutex_lock(&lock);
                    MINER_COUNT++;
                    GOLD -= 100;
                    print_gold(GOLD);
                    pthread_mutex_unlock(&lock);
                } else {
                    print_fail("Not enough gold!");
                }
                break;

            case 's':
                if (GOLD - 10 >= 0) {
                    print_msg("Soldier created!");
                    soldier(1);
                } else {
                    print_fail("Not enough gold!");
                }
                break;

            case 'x':
                if (GOLD - 100 >= 0) {
                    print_msg("10 x soldiers created!");
                    soldier(10);
                } else {
                    print_fail("Not enough gold!");
                }
                break;

            case 'q':
                game_end(ZOMBIE_COUNT);
                break;
        }
    }
}
