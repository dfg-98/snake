#include <stdio.h>
#include <stdlib.h>

#include "typedef.h"
#include "board.h"
#include "snake.h"
#include "utils.h"

int FRUITS_LEFT = 5;
int GROWING = 0;

board_t *board;
snake_t *snake;

bool EVEN_DIM;
bool MOVE_ON_WIDTH;
bool IS_ON_TRACK = false;

void spawn_fruits(board_t *board)
{
    int i;
    for (i = 0; i < FRUITS_LEFT; i++)
    {
        int x = rand() % (board->width - 1);
        int y = rand() % (board->height - 1);
        if (get_cell_state(board, x, y) == EMPTY)
        {
            set_cell_state(board, x, y, FOOD);
        }
        else
        {
            i--;
        }
    }
}

// Check if is on track
bool is_on_track(int x, int y)
{

    if (MOVE_ON_WIDTH && is_even(y))
    {
        return true;
    }
    else if (!MOVE_ON_WIDTH && is_even(x))
    {
        return true;
    }
    return false;
}

point_t compute_next_move(board_t *board, snake_t *snake);

int main(int argc, char const *argv[])
{
    int width = atoi(argv[1]);
    int height = atoi(argv[2]);
    // int width = 6;
    // int height = 7;
    printf(" Creando tablero de  %d x %d \n", width, height);
    board = create_board(width, height);
    snake = snake_create(board->width / 2, board->height / 2, board);
    spawn_fruits(board);


    // Set Moving Constants
    if (is_even(width))
    {
        EVEN_DIM = true;
        MOVE_ON_WIDTH = false;
    }
    else if (is_even(height))
    {
        EVEN_DIM = true;
        MOVE_ON_WIDTH = true;
    }
    else if (width > height)
    {
        EVEN_DIM = false;
        MOVE_ON_WIDTH = false;
    }
    else
    {
        EVEN_DIM = false;
        MOVE_ON_WIDTH = true;
    }
    // Check if is on track
    // IS_ON_TRACK = is_on_track(snake->x, snake->y);
    print_board(board);
    // Main Loop
    while (true)
    {
        point_t next_move = compute_next_move(board, snake);
        if (is_invalid_point(next_move))
        {
            break;
        }
        if (get_cell_state(board, next_move.x, next_move.y) == FOOD)
        {
            FRUITS_LEFT--;
            GROWING += 3;
        }
        snake_move(snake, next_move.x, next_move.y, board, GROWING > 0);
        if (GROWING > 0)
        {
            GROWING--;
        }
        if (FRUITS_LEFT == 0)
        {
            FRUITS_LEFT = 5;
            if (get_free_cells(board) < 5)
            {
                FRUITS_LEFT = get_free_cells(board);
            }
        }
        print_board(board);
        printf("\n");
        char a;
        scanf("%c", &a);
    }

    destroy_snake(snake, board);
    destroy_board(board);

    return 0;
}


point_t compute_next_move(board_t *board, snake_t *snake)
{
    int x = snake->head->x;
    int y = snake->head->y;
    // UP RIGHT DOWN LEFT
    point_t possible_move[4];
    if (y > 0 && is_free_cell(board, x, y - 1))
    {
        possible_move[0] = create_point(x, y - 1);
    }
    else
    {
        possible_move[0] = create_point(-1, -1);
    }
    if (x < board->width - 1 && is_free_cell(board, x + 1, y))
    {
        possible_move[1] = create_point(x + 1, y);
    }
    else
    {
        possible_move[1] = create_point(-1, -1);
    }
    if (y < board->height - 1 && is_free_cell(board, x, y + 1) )
    {
        possible_move[2] = create_point(x, y + 1);
    }
    else
    {
        possible_move[2] = create_point(-1, -1);
    }
    if (x > 0 && is_free_cell(board, x - 1, y))
    {
        possible_move[3] = create_point(x - 1, y);
    }
    else
    {
        possible_move[3] = create_point(-1, -1);
    }

    int valids = 0;
    point_t last_valid;
    for (int i = 0; i < 4; i++)
    {
        if (!is_invalid_point(possible_move[i]))
        {
            valids++;
            last_valid = possible_move[i];
            printf("Valid point: (%d, %d) \n", possible_move[i].x, possible_move[i].y);
        }
    }
    if (valids == 0)
    {
        return create_point(-1, -1);
    }
    if (valids == 1)
    {
        return last_valid;
    }

    if (MOVE_ON_WIDTH)
    {
        if (is_even(y))
        {
            if (x == board->width - 1)
            {
                if (y == board->height - 1)
                {
                }
            }
            else if (y < board->height - 1 && get_cell_state(board, x, y + 1) == EMPTY)
            {
                return create_point(x, y + 1);
            }
            else if (x > 0 && get_cell_state(board, x - 1, y) == EMPTY)
            {
                return create_point(x - 1, y);
            }
            else if (y > 0 && get_cell_state(board, x, y - 1) == EMPTY)
            {
                return create_point(x, y - 1);
            }
        }
        else
        {
            if (y < board->height - 1 && get_cell_state(board, x, y + 1) == EMPTY)
            {
                return create_point(x, y + 1);
            }
            else if (x > 0 && get_cell_state(board, x - 1, y) == EMPTY)
            {
                return create_point(x - 1, y);
            }
            else if (y > 0 && get_cell_state(board, x, y - 1) == EMPTY)
            {
                return create_point(x, y - 1);
            }
            else if (x < board->width - 1 && get_cell_state(board, x + 1, y) == EMPTY)
            {
                return create_point(x + 1, y);
            }
        }
    }

    while (true)
    {
        int random = rand() % 4;
        if (!is_invalid_point(possible_move[random]))
        {
            return possible_move[random];
        }
    }
}
