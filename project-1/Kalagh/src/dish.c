#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

#include "mother.h"
#include "dish.h"

pthread_mutex_t mutex_set_state = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_full_dishes = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  condition_var   = PTHREAD_COND_INITIALIZER;


int capacity;

void dishes_init(int size) {
    capacity = size;
    dishes = malloc(sizeof(struct dish) * capacity);

    for(int i = 0; i < size; i++) {
        dishes[i].state = EMPTY;
    }
}

int dishes_get_state(int i) {
    return dishes[i].state;
}

void dishes_set_state(int i, int state) {
    pthread_mutex_lock(&mutex_set_state);
    printf("Set dish %d state to %d\n", i, state);
    dishes[i].state = state;
    pthread_mutex_unlock(&mutex_set_state);
}

int dishes_get_size() {
    return capacity;
}

void dishes_delete() {
    free(dishes);
}

int dishes_get_full_dish() {

    int return_value = -1;
    pthread_mutex_lock(&mutex_full_dishes);

    printf("We are inside the mutex\n");
    while(1) {

        for(int i = 0; i < capacity; i++) {
            if(dishes[i].state == FULL) {
                printf("Found dish %d\n", i);
                return_value = i;
                break;
            }
        }

        if(return_value != -1) {
            break;
        }

        int k = 0;
        for(int i = 0; i < capacity; i++) {
            if(dishes[i].state == EMPTY) {
                k++;
            }
        }


        if(k == capacity) {
            printf("Waking up mother to fill the dishes\n");
            mother_fill_dishes();
        }
    }

    pthread_mutex_unlock(&mutex_full_dishes);
    return return_value;
}
