#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "child.h"
#include "dish.h"

void children_init(int size) {
    children = malloc(sizeof(struct child) * size);
}

void children_run(int i) {
    int rc = pthread_create(&children[i].thread, NULL, run, (void *) &i);

    if(rc) {
        fprintf(stderr, "Error pthread_create() return code: %d\n", rc);
    }
}

void children_eat(int i) {
    children[i].state = EATING;
    sleep(EAT_TIME);

}

void children_finish_eating(int i) {

}

void children_ready_to_eat(int i) {
    children[i].state = HUNGRY;
}

void children_delete() {
    free(children);
}

void *run(void *element) {
    int i = *((int *) element);

    while(1) {
        children_ready_to_eat(i);
        children_eat(i);
        children_finish_eating(i);
    }
}
