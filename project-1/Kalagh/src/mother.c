#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "dish.h"
#include "mother.h"

int food_capacity;

void mother_init(int food) {
    mom.state = MOM_ASLEEP;
    food_capacity = food;
}

void mother_goto_sleep() {
    mom.state = MOM_ASLEEP;
    printf("Mom gone to sleep\n");
}

void mother_food_ready() {

}

void mother_fill_dishes() {
    mother_wake_up();
    int capacity = dishes_get_size();

    for(int i = 0; i < capacity; i++) {
        printf("Food capacity: %d\n", food_capacity);
        if(food_capacity > 0) {
            sleep(FOOD_GATHER);
            dishes_set_state(i, FULL);
            printf("Mom collected food %d\n", i);
            food_capacity--;
        } else {
            printf("No food left :(");
            exit(0);
        }
    }

    mother_food_ready();
    mother_goto_sleep();
}

void mother_wake_up() {
    mom.state = MOM_AWAKE;
    printf("Mom woke up\n");
}
