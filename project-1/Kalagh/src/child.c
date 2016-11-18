#include <unistd.h>

#include "child.h"

void child_eat(struct child *current_child) {
    current_child->state = EATING;
    sleep(EAT_TIME);
}
