#include <unistd.h>

#include "dish.h"
#include "mother.h"

void mother_init() {
    mom.state = MOM_ASLEEP;
}

void mother_goto_sleep() {
    mom.state = MOM_ASLEEP;
}

void mother_food_ready() {

}

void mother_fill_dishes() {
    mother_wake_up();
    int capacity = dishes_get_size();

    for(int i = 0; i < capacity; i++) {
        sleep(FOOD_GATHER);
        dishes_set_state(i, FULL);
    }

    mother_food_ready();
    mother_goto_sleep();
}

void mother_wake_up() {
    mom.state = MOM_AWAKE;
}
