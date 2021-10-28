#ifndef __BOARD_H__
#define __BOARD_H__

typedef enum
{
    EMPTY,
    SNAKE_BODY,
    SNAKE_HEAD,
    FOOD
} cell_state;

typedef struct
{
    int width;
    int height;
    cell_state *cells;
} board_t;

// Initialize the board_t
board_t *create_board(int width, int height);
// Destroy the board_t
void destroy_board(board_t *b);
// Print the board_t
void print_board(board_t *b);

// Get cell state
cell_state get_cell_state(board_t *b, int x, int y);

// Set cell state
void set_cell_state(board_t *b, int x, int y, cell_state state);

// returns free cells in the board_t
int get_free_cells(board_t *b);

#endif