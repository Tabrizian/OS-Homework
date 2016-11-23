#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

#include "child.h"
#include "dish.h"

pthread_mutex_t mutex_thread = PTHREAD_MUTEX_INITIALIZER;
int num;

void children_init(int size) {
    children = malloc(sizeof(struct child) * size);
    num = size;

}

void children_run(int i) {

    pthread_mutex_lock(&mutex_thread);
    int d = i;
    printf("Child %d\n", i);
    int rc = pthread_create(&(children[i].thread), NULL, &run, (void *) &d);

    if(rc) {
        printf("Error pthread_create() return code: %d\n", rc);
    }
    pthread_mutex_unlock(&mutex_thread);
}

void children_eat(int i, int dish_id) {
    children[i].state = EATING;
    printf("Children %d is now eating dish %d\n", i, dish_id);
    dishes_set_state(dish_id, HALF);
    sleep(EAT_TIME);
    dishes_set_state(dish_id, EMPTY);
    children_finish_eating(i);
}

void children_finish_eating(int i) {
    children[i].state = PLAYING;
    printf("Children %d is now playing\n", i);
    children_play(i);
}

void children_ready_to_eat(int i) {
    children[i].state = HUNGRY;
    printf("Children %d state is now hungry\n", i);
    int dish_id = dishes_get_full_dish(i);
    printf("Children %d found empty dish %d\n", i, dish_id);
    children_eat(i, dish_id);

}

void children_play(int i) {
    children[i].state = PLAYING;
    sleep(PLAY_TIME);
    printf("Children %d play finished\n", i);
}


void children_delete() {
    free(children);
}

void children_finish() {
    for (int i = 0; i < num; i++) {
        pthread_join(children[i].thread, NULL);
    }
}

void *run(void *element) {
    int i = *((int *) element);

    printf("Child run %d\n", i);
    printf("Thread for child %d created\n", i);
    while(1) {
        children_ready_to_eat(i);
    }
}
