#include "board.h"
#include <stdlib.h>
#include <stdio.h>

board_t *create_board(int width, int height)
{
    board_t *b = malloc(sizeof(board_t));
    b->width = width;
    b->height = height;
    b->cells = malloc(sizeof(cell_state) * width * height);
    for (int i = 0; i < width * height; i++)
    {
        b->cells[i] = EMPTY;
    }
    return b;
}

void destroy_board(board_t *b)
{
    free(b->cells);
    free(b);
}

// Returns the cell at the given coordinates.
cell_state get_cell_state(board_t *b, int x, int y)
{
    return b->cells[y * b->width + x];
}

// Sets the cell at the given coordinates to the given state.
void set_cell_state(board_t *b, int x, int y, cell_state state)
{
    b->cells[y * b->width + x] = state;
}

// Returns the number of free cells in the board_t.
int get_free_cells(board_t *b)
{
    int free_cells = 0;
    for (int i = 0; i < b->width * b->height; i++)
    {
        if (b->cells[i] == EMPTY)
        {
            free_cells++;
        }
    }
    return free_cells;
}

void print_board(board_t *b)
{
    for (int y = 0; y < b->height; y++)
    {
        for (int x = 0; x < b->width; x++) 
        {
            switch (get_cell_state(b, x, y))
            {
                case EMPTY:
                    printf(".");
                    break;
                case SNAKE_HEAD:
                    printf("@");
                    break;
                case SNAKE_BODY:
                    printf("o");
                    break;
                case FOOD:
                    printf("x");
                    break;
            }
        }
        printf("\n");
    }
}

bool is_free_cell(board_t *b, int x, int y)
{
    return get_cell_state(b, x, y) == EMPTY || get_cell_state(b, x, y) == FOOD;
}