#ifndef CHILD_H
#define CHILD_H

#define EAT_TIME 5
#define PLAY_TIME 3

#define EATING 1
#define PLAYING 2
#define HUNGRY 3

struct child {
    int state;
    pthread_t thread;
};

struct child *children;

void children_init(int size);
void children_run(int i);
void children_eat(int i, int dish_id);
void children_finish_eating(int i);
void children_ready_to_eat(int i);
void children_play(int i);
void children_delete();

void *run(void *element);

#endif
