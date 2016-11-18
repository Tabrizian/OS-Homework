#include <stdlib.h>

#include "mother.h"
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

int dishes_get_size() {
    return capacity;
}

void dishes_delete() {
    free(dishes);
}

int dishes_get_full_dish() {

    while(1) {
        for(int i = 0; i < capacity; i++) {
            if(dishes[i].state == FULL) {
                return i;
            }
        }

        mother_fill_dishes();
    }

}
