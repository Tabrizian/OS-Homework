#include <unistd.h>

#include "mother.h"

void mother_fill_dishes(struct mother *mom, struct dish dishes[], int size) {
    mom->state = MOM_AWAKE;
    for (int i = 0; i < size; i++) {
        sleep(FOOD_GATHER);
        dishes[i].state = 1;
    }
}
