#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "typedef.h"
#include "board.h"
#include "snake.h"
#include "utils.h"
#include "bfs.h"
#include "queue.h"
#include "stack.h"

int FRUITS_LEFT = 5;
int GROWING = 0;

board_t *board;
snake_t *snake;

bool EVEN_DIM;
bool MOVE_ON_WIDTH;
stack_t MOVEMENT_STACK = {0, NULL};

void spawn_fruits(board_t *board)
{
    if (FRUITS_LEFT == get_free_cells(board))
    {
        for (int i = 0; i < board->width * board->height; i++)
        {
            if (board->cells[i] == EMPTY)
            {
                board->cells[i] = FOOD;
                break;
            }
        }
        return;
    }
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
    srand((unsigned)time(NULL));
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
    system("clear");
    print_board(board);
    printf("\nPuntuacion: %d", snake->length - 3);
    printf("\n");
    // Main Loop
    while (true)
    {
        sleep(1);
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
            // printf("free cells %d \n", get_free_cells(board));
            if (get_free_cells(board) < 5)
            {
                FRUITS_LEFT = get_free_cells(board);
            }

            spawn_fruits(board);
        }
        system("clear");
        print_board(board);
        printf("\nPuntuacion: %d", snake->length - 3);
        printf("\n");
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
    get_possible_moves(x, y, board, possible_move);

    int valids = 0;
    point_t last_valid;
    for (int i = 0; i < 4; i++)
    {
        if (!is_invalid_point(possible_move[i]))
        {
            valids++;
            last_valid = possible_move[i];
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

    if (EVEN_DIM)
    {

        if (MOVE_ON_WIDTH)
        {
            if (is_even(y))
            {
                if (x == 0)
                {
                    if (y == 0)
                    {
                        return create_point(x + 1, y);
                    }
                    return create_point(x, y - 1);
                }
                if (x > 0 && x < board->width - 1)
                {
                    return create_point(x + 1, y);
                }
                return create_point(x, y + 1);
            }
            else if (!is_even(y))
            {
                if (x == 0)
                {
                    return create_point(x, y - 1);
                }
                if ((x > 1) || (x == 1 && y == board->height - 1))
                {
                    return create_point(x - 1, y);
                }
                else if (x == 1)
                {
                    return create_point(x, y + 1);
                }
            }
        }

        else
        {
            if (is_even(x))
            {
                if (y == 0)
                {
                    if (x == 0)
                    {
                        return create_point(x, y + 1);
                    }
                    return create_point(x - 1, y);
                }
                if (y > 0 && y < board->height - 1)
                {
                    return create_point(x, y + 1);
                }
                return create_point(x + 1, y);
            }
            else if (!is_even(x))
            {
                if (y == 0)
                {
                    return create_point(x - 1, y);
                }
                if ((y > 1) || (y == 1 && x == board->width - 1))
                {
                    return create_point(x, y - 1);
                }
                else if (y == 1)
                {
                    return create_point(x + 1, y);
                }
            }
        }
    }

    if (MOVEMENT_STACK.count == 0)
    {
        while (MOVEMENT_STACK.top != NULL)
        {
            pop(&MOVEMENT_STACK);
        }
        MOVEMENT_STACK = bfs(board, snake->head->x, snake->head->y);
    }
    if (MOVEMENT_STACK.count == 0)
    {
        return last_valid;
    }
    point_t next_move = pop(&MOVEMENT_STACK);
    bool is_valid_next = false;
    for (int i = 0; i < 4; i++)
    {
        if (possible_move[i].x == next_move.x && possible_move[i].y == next_move.y)
        {
            is_valid_next = true;
        }
    }
    if (is_valid_next)
    {
        return next_move;
    }
    while (MOVEMENT_STACK.top != NULL)
    {
        pop(&MOVEMENT_STACK);
    }
    return last_valid;
}
