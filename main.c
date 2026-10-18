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

WINDOW *initWindow();

int main(void) {
    srand(time(0));

    WINDOW *window = initWindow();

    init_pair(TILE_FIELD, COLOR_BLACK, COLOR_FIELD);
    init_pair(TILE_SNACK, COLOR_BLACK, COLOR_SNACK);
    init_pair(TILE_SNAKE, COLOR_BLACK, COLOR_SNAKE);

    drawBoard();
    Snake snake;
    Segment *segments = malloc(sizeof(Segment)*WIDTH*HEIGHT);
    Snack snack;
    createSnack(&snack);
    initSnake(&snake, segments);

    struct timespec frameTime;
    frameTime.tv_sec = 0;
    frameTime.tv_nsec = 100000000L;
    // frameTime.tv_nsec = 500000000L;

    char ch;
    nodelay(window, TRUE);
    while(ch != 'q') {

        // check for wall collision
        if (collision(snake, segments)) {
            break;
        }

        ch = getch();

        if (snake.head->position[0] == snack.position[0] &&
            snake.head->position[1] == snack.position[1]) {
            createSnack(&snack);
            snake.length += 1;
            // segments[snake.length-1].position[0] = 0;
            // segments[snake.length-1].position[1] = 0;
            for (int i = 0; i < snake.length-1; i++) {
                if (segments[i].next == NULL) {
                    segments[i].next = &segments[snake.length-1];
                    break;
                }
            }
            segments[snake.length-1].next = NULL;
        }

        // if (ch == MOVE_UP && (snake.direction[0] != 0 && snake.direction[1] != -1)) {
        if (ch == MOVE_UP) {
            snake.direction[0] = 0;
            snake.direction[1] = -1;
        };
        if (ch == MOVE_DOWN) {
            snake.direction[0] = 0;
            snake.direction[1] = 1;
        };
        if (ch == MOVE_LEFT) {
            snake.direction[0] = -1;
            snake.direction[1] = 0;
        };
        if (ch == MOVE_RIGHT) {
            snake.direction[0] = 1;
            snake.direction[1] = 0;
        };
        updateSnake(&snake, segments);

        // draw everything after doing calculations
        drawBoard();
        drawSnack(snack);
        drawSnake(snake, segments);
        nanosleep(&frameTime, NULL);
        refresh();
    }
    nodelay(window, FALSE);

    free(segments);
    endwin();

    printf("Score: %d\n", snake.length-2);
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

