#ifndef MOTHER_H
#define MOTHER_H
#define MOM_AWAKE 1
#define MOM_ASLEEP 0
#define FOOD_GATHER 10

struct mother {
    int state;
};

struct mother mom;

void mother_init();
void mother_goto_sleep();
void mother_food_ready();
void mother_fill_dishes();
void mother_wake_up();

#endif
