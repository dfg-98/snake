#include "board.h"

#ifndef __SNAKE_H__
#define __SNAKE_H__

#include <stdbool.h>


typedef struct snake_segment_t {
    int x;
    int y;
    struct snake_segment_t *next;
} snake_segment_t;

typedef struct {
    snake_segment_t *head;
    snake_segment_t *tail;
    int length;
    
} snake_t;


// Create snake
snake_t *snake_create(int x, int y, board_t *board);

// Destroy snake
void destroy_snake(snake_t *snake, board_t *board);

// Move snake
void snake_move(snake_t *snake, int x, int y, board_t *board, bool growing);

#endif