#include <stdio.h>

void print_begin_message(int m, int n, int t) {
    printf("There are %d baby crows, %d feeding pots, and %d feedings\n", m,
            n, t);
}

int main() {
    int m, n, t;
    printf("Enter m, n, t\n");
    scanf("%d %d %d", &m, &n, &t);

    if(m == 0) {
        m = 10;
    }

    if(n == 0) {
        n = 10;
    }

    if(t == 0) {
        t = 10;
    }

    print_begin_message(m, n, t);
}
