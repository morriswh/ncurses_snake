#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <ncurses.h>
#include <time.h>

#include "game_objects.c"

#define MOVE_UP 119
#define MOVE_DOWN 115
#define MOVE_RIGHT 100
#define MOVE_LEFT 97
#define ESC 27

const struct dimensions {
    int width;
    int height;
} dimensions;

int main(void) {
    srand(time(0));

    Snake snake;
    Segment segments[20];
    initSnake(&snake, segments);

        printf("===================\n");
        for (int i = 0; i < snake.length; i++) {
            printf("%d, %d\n", segments[i].position[0], segments[i].position[1]);
        }

    int count = 0;
    while(count < 1) {
        count++;

        // if (snake.head->position[0] == snack.position[0] &&
        //     snake.head->position[1] == snack.position[1]) {
        if (true) {
            snake.length += 1;
            segments[snake.length-1].position[0] = 3;
            segments[snake.length-1].position[1] = 7;
            for (int i = 0; i < snake.length-1; i++) {
                if (segments[i].next == NULL) {
                    segments[i].next = &segments[snake.length-1];
                    break;
                }
            }
            segments[snake.length-1].next = NULL;
        }

        updateSnake(&snake, segments);
        printf("===================\n");
        for (int i = 0; i < snake.length; i++) {
            printf("%d, %d\n", segments[i].position[0], segments[i].position[1]);
        }

        system("sleep 0.1");

        refresh();
    }

    return EXIT_SUCCESS;
}

WINDOW *initWindow() {
    WINDOW *window = initscr();
	raw();				/* Line buffering disabled	*/
	keypad(stdscr, TRUE);		/* We get F1, F2 etc..		*/
	noecho();			/* Don't echo() while we do getch */
    curs_set(0);
    start_color();
    return window;
}

