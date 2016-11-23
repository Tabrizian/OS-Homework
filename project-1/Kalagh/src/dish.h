#ifndef DISH_H
#define DISH_H

#define FULL 1
#define HALF 2
#define EMPTY 3

struct dish {
    int state;
};

struct dish *dishes;

void dishes_init(int size);
int dishes_get_state(int i);
void dishes_set_state(int i, int state);
int dishes_get_size();
void dishes_delete();
int dishes_get_full_dish(int i);

#endif
