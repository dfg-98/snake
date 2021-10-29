#ifndef __UTILS_H_
#define __UTILS_H_

#include <stdlib.h>
#include "typedef.h"
#include "board.h"

// Returns true if given interger is even
bool is_even(int n);

void get_possible_moves(int x, int y, board_t *board, point_t *possible_moves);

#endif