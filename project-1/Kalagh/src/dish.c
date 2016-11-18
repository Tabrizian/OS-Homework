#include <stdlib.h>

#include "dish.h"

int capacity;

void dishes_init(int size) {
    capacity = size;
    dishes = malloc(sizeof(struct dish) * capacity);

    for(int i = 0; i < size; i++) {
        dishes[i].state = FULL;
    }
}

int dishes_get_state(int i) {
    return dishes[i].state;
}

void dishes_set_state(int i, int state) {
    dishes[i].state = state;
}

void dishes_delete() {
    free(dishes);
}
