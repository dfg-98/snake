
#include "bfs.h"
#include "queue.h"
#include "typedef.h"
#include "utils.h"
#include "stack.h"
#include <stdlib.h>


stack_t bfs(board_t *board, int x, int y){

    
    bool visited[board->height][board->width];
    for (int i = 0; i < board->height; i++) {
        for (int j = 0; j < board->width; j++) {
            visited[i][j] = false;
        }
    }

    queue_t q = init_queue();
    queue_t garbage = init_queue();
    node_t *node = malloc(sizeof(node_t));
    node->x = x;
    node->y = y;
    node->d = 0;
    node->parent = NULL;
    visited[y][x] = true;
    enqueue(&q, node);

    while(q.count > 0) {
        node_t *current = dequeue(&q);
        enqueue(&garbage, current);
        if(get_cell_state(board, current->x, current->y) == FOOD) {
            stack_t path;
            path.count = 0;
            path.top = NULL;
            while (current->parent != NULL && !(current->x == x && current->y == y) ) {
                push(&path, (point_t){current->x, current->y} );
                current = current->parent;
            }
            delete_queue(&q);
            delete_queue(&garbage);
            return path;
        }

        point_t possible_moves[4];
        get_possible_moves(current->x, current->y, board, possible_moves);
        for (int i = 0; i < 4; i++) {
            if(!is_invalid_point(possible_moves[i]) && !visited[possible_moves[i].y][possible_moves[i].x] && is_free_cell(board, possible_moves[i].x, possible_moves[i].y) )
            {
                node_t *next = malloc(sizeof(node_t));
                next->x = possible_moves[i].x;
                next->y = possible_moves[i].y;
                next->d = current->d + 1;
                next->parent = current;
                visited[possible_moves[i].y][possible_moves[i].x] = true;
                enqueue(&q, next);
            }
        }
        
    }
    return (stack_t){0, NULL};
}