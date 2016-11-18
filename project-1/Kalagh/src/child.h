#ifndef CHILD_H
#define CHILD_H

#define EAT_TIME 5
#define PLAY_TIME 3

#define EATING 1
#define PLAYING 2
#define HUNGRY 3

struct child {
    int state;
}

void child_eat(struct child *current_child);

#endif
