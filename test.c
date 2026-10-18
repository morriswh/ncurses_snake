#include <stdio.h>
// #include <inttypes.h>
#include <stdlib.h>

typedef struct Head_t Head;
typedef struct Test_t Test;

typedef struct Head_t {
    int length;
    Test *head;
} head;

typedef struct Test_t {
    int x;
    int y;
    Test *next;
} Test;

void assignValue(Test *test) {
    test->x = 5;
    test->y = 6;
}

int main() {

    Head h;
    Test t[3];

    h.length = 3;
    h.head = &t[0];

    // t[0].x = 3;
    // t[0].y = 5;
    assignValue(&t[0]);
    t[1].x = 7;
    t[1].y = 8;
    t[2].x = 1;
    t[2].y = 11;

    t[0].next = &t[1];
    t[1].next = &t[2];
    t[2].next = NULL;

    if (t[2].next->next == NULL) {
        printf("zooted\n");
    }
    exit(0);

    printf("%d\n", h.head->y);
    printf("%d\n", h.head->next->y);
    printf("%d\n", h.head->next->next->y);

    for (int i = 0; i < h.length; i++) {
        if (t[i].next->next == NULL) {
            printf("HERE\n");
            t[i].next->next = h.head;
            h.head = t[i].next;
            t[i].next = NULL;
            break;
        }
    }

    printf("%d\n", h.head->y);
    printf("%d\n", h.head->next->y);
    printf("%d\n", h.head->next->next->y);

    for (int i = 0; i < h.length; i++) {
        if (t[i].next->next == NULL) {
            printf("HERE\n");
            t[i].next->next = h.head;
            h.head = t[i].next;
            t[i].next = NULL;
            break;
        }
    }

    printf("%d\n", h.head->y);
    printf("%d\n", h.head->next->y);
    printf("%d\n", h.head->next->next->y);

    return EXIT_SUCCESS;
}
