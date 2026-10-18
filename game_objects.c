#define WIDTH 16
#define HEIGHT 16

#define COLOR_FIELD 94
#define COLOR_SNAKE 35
#define COLOR_SNACK 124 
#define COLOR_DEATH 214

#define TILE_FIELD 94
#define TILE_SNAKE 35
#define TILE_SNACK 124 
#define TILE_DEATH 214

typedef struct Snake_t Snake;
typedef struct Segment_t Segment;
typedef struct Snack_t Snack;

typedef struct Snake_t {
    int length;
    int direction[2];
    Segment *head;
} Snake;

typedef struct Segment_t {
    int position[2];
    Segment *next;
} Segment;

typedef struct Snack_t {
    int position[2];
} Snack;

void initSnake(Snake *snake, Segment *segments) {
    snake->length = 2;
    snake->direction[0] = 0;
    snake->direction[1] = -1;

    snake->head = &segments[0];
    for (int i = 0; i < snake->length; i++) {
        segments[i].position[0] = 8;
        segments[i].position[1] = 8+i;
        segments[i].next = &segments[i+1];
    }
    segments[snake->length-1].next = NULL;
}

void drawBoard() {
    attron(COLOR_PAIR(TILE_FIELD));
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            move(i,2*j);
            printw("  ");
        }
    }
    attroff(COLOR_PAIR(TILE_FIELD));
}

void createSnack(Snack *snack) {
    float randX = (float)rand()/RAND_MAX; 
    float randY = (float)rand()/RAND_MAX; 
    snack->position[0] = randX * WIDTH;
    snack->position[1] = randY * HEIGHT;
}

void drawSnack(Snack snack) {
    move(snack.position[1], 2*snack.position[0]);
    attron(COLOR_PAIR(TILE_SNACK));
    printw("  ");
    attroff(COLOR_PAIR(TILE_SNACK));
}

void updateSnake(Snake *snake, Segment *segment) {
    for (int i = 0; i < snake->length; i++) {
        if (segment[i].next != NULL) {
            if (segment[i].next->next == NULL) {
                segment[i].next->next = snake->head;
                snake->head = segment[i].next;
                segment[i].next = NULL;
                break;
            }
        }
    }
    snake->head->position[0] = snake->head->next->position[0] + snake->direction[0];
    snake->head->position[1] = snake->head->next->position[1] + snake->direction[1];
}

void drawSnake(Snake snake, Segment *segment) {
    attron(COLOR_PAIR(TILE_SNAKE));
    for (int i = 0; i < snake.length; i++) {
        move(segment[i].position[1], 2*segment[i].position[0]);
        printw("  ");
    }
    attroff(COLOR_PAIR(TILE_SNAKE));
}

bool collision(Snake snake, Segment *segment) {
    if (snake.head->position[0] < 0 || 
        snake.head->position[0] >= WIDTH ||
        snake.head->position[1] < 0 || 
        snake.head->position[1] >= HEIGHT) {
            return true;
    }
    for (int i = 0; i < snake.length; i++) {
        if (snake.head->position[0] == segment[i].position[0] &&
            snake.head->position[1] == segment[i].position[1] &&
            snake.head != &segment[i]) {
            return true;
        }
    }
    return false;
}

