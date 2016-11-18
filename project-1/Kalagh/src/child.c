#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "child.h"
#include "dish.h"

int capacity;

void children_init(int size) {
    children = malloc(sizeof(struct child) * size);
    capacity = size;

}

void children_run(int i) {
    int rc = pthread_create(&children[i].thread, NULL, run, (void *) &i);

    if(rc) {
        fprintf(stderr, "Error pthread_create() return code: %d\n", rc);
    }
}

void children_eat(int i, int dish_id) {
    children[i].state = EATING;
    dishes_set_state(dish_id, HALF);
    sleep(EAT_TIME);
    dishes_set_state(dish_id, EMPTY);
    children_finish_eating(i);
}

void children_finish_eating(int i) {
    children[i].state = PLAYING;
    children_play(i);
}

void children_ready_to_eat(int i) {
    children[i].state = HUNGRY;
    int dish_id = dishes_get_full_dish();
    children_eat(i, dish_id);

}

void children_play(int i) {
    children[i].state = PLAYING;
    sleep(PLAY_TIME);
}


void children_delete() {
    free(children);
}

void children_finish() {
    for (int i = 0; i < capacity; i++) {
        pthread_join(children[i].thread, NULL);
    }
}

void *run(void *element) {
    int i = *((int *) element);

    while(1) {
        printf("Running child %d\n", i);
        children_ready_to_eat(i);
    }
}
