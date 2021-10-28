#include "snake.h"
#include "typedef.h"
#include "stdio.h"
#include "stdlib.h"

// Function: create_snake
// Purpose: creates a snake
snake_t *snake_create(int x, int y, board_t *board)
{
    snake_t *snake = malloc(sizeof(snake_t));
    snake->head = malloc(sizeof(snake_segment_t));
    snake->head->x = x;
    snake->head->y = y;
    set_cell_state(board, x, y, SNAKE_HEAD);
    snake_segment_t *current_segment = snake->head;
    for (uint i = 1; i < 3; i++)
    {
        snake_segment_t *segment = malloc(sizeof(snake_segment_t));
        segment->x = x - i;
        segment->y = y;
        set_cell_state(board, segment->x, segment->y, SNAKE_BODY);
        current_segment->next = segment;
        current_segment = segment;
        segment->next = NULL;
    }
    return snake;
}

// Function: destroy_snake
// Purpose: destroys a snake
void destroy_snake(snake_t *snake, board_t *board)
{
    snake_segment_t *current_segment = snake->head;
    while (current_segment != NULL)
    {
        set_cell_state(board, current_segment->x, current_segment->y, EMPTY);
        snake_segment_t *next_segment = current_segment->next;
        free(current_segment);
        current_segment = next_segment;
    }
}

// Function: snake_move
// Purpose: moves the snake
void snake_move(snake_t *snake, int x, int y, board_t *board, bool growing)
{
    // Set Heaad as Body
    set_cell_state(board, snake->head->x, snake->head->y, SNAKE_BODY);
    // Add new head in the new position
    snake_segment_t *new_segment = malloc(sizeof(snake_segment_t));
    new_segment->x = x;
    new_segment->y = y;
    new_segment->next = snake->head;
    snake->head = new_segment;
    set_cell_state(board, x, y, SNAKE_HEAD);

    // If the snake is growing, don't remove the tail
    if (!growing)
    {
        // Remove the tail
        snake_segment_t *current_segment = snake->head;
        while (current_segment->next->next != NULL)
        {
            current_segment = current_segment->next;
        }
        set_cell_state(board, current_segment->next->x, current_segment->next->y, EMPTY);
        free(current_segment->next);
        current_segment->next = NULL;
    }
}
