#ifndef MOTHER_H
#define MOTHER_H
#define MOM_AWAKE 1
#define MOM_ASLEEP 0
#define FOOD_GATHER 10

#include "dish.h"

struct mother {
    int state;
};

void mother_fill_dishes(struct mother *mom, struct dish dishes[], int size);
#endif
