#ifndef __UTILS_H_
#define __UTILS_H_

#include <stdlib.h>
#include "typedef.h"

// Returns true if given interger is even
bool is_even(int n)
{
    return n % 2 == 0;
}

void get_possible_moves(int x, int y, board_t *board, point_t *possible_moves)
{
    // UP RIGHT DOWN LEFT
    
    if (y > 0 && is_free_cell(board, x, y - 1))
    {
        possible_moves[0] = create_point(x, y - 1);
    }
    else
    {
        possible_moves[0] = create_point(-1, -1);
    }
    if (x < board->width - 1 && is_free_cell(board, x + 1, y))
    {
        possible_moves[1] = create_point(x + 1, y);
    }
    else
    {
        possible_moves[1] = create_point(-1, -1);
    }
    if (y < board->height - 1 && is_free_cell(board, x, y + 1) )
    {
        possible_moves[2] = create_point(x, y + 1);
    }
    else
    {
        possible_moves[2] = create_point(-1, -1);
    }
    if (x > 0 && is_free_cell(board, x - 1, y))
    {
        possible_moves[3] = create_point(x - 1, y);
    }
    else
    {
        possible_moves[3] = create_point(-1, -1);
    }

}


#endif