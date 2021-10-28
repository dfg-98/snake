
#include <stdlib.h>
#include <stdbool.h>
#include "board.h"
#include "typedef.h"
#include "utils.h"

typedef struct node
{
    // Esta es la distancia al nodo origen
    int g;
    // Esta es la distancia al nodo destino
    int h;
    // Esta es la suma de g y h
    int f;
    
    // Position 
    int x, y;
    bool visited;

    //Probablemente se borre
    struct node *top;
    struct node *left;
    struct node *right;
    struct node *down;
} bfs_node;

typedef struct s_node
{
    int x; y;
    //Valor del nodo
    int d;
    // BFS parent
    struct s_node *parent;
    //Nodo siguiente
    struct s_node *next;
    // struct s_node *prev;
} node_t;

typedef struct stack
{
    int count;
    //El tope del stack
    node_t *top;

} stack_t;

stack_t *create_stack()
{
    stack_t *stack = (stack_t *)malloc(sizeof(stack_t));
    stack->count = 0;
    stack->top = NULL;
    return stack;
}

void push(stack_t *stack, node_t *node)
{
    if (stack->count == 0)
    {
        stack->top = node;
        stack->count++;
    }
    else
    {
        node->next = stack->top;
        stack->top = node;
        stack->count++;
    }
}

node_t *pop(stack_t *stack)
{
    if (stack->count == 0)
    {
        printf("Stack is empty\n");
    }
    else
    {
        node_t *node = stack->top;
        stack->top = stack->top->next;
        stack->count--;
        return node;
    }
}

stack_t *top(stack_t *stack)
{
    if (stack->count == 0)
    {
        printf("Stack is empty\n");
        return NULL;
    }
    else
    {
        return stack->top;
    }
}

void destroy_stack(stack_t *stack)
{
    while (stack->count > 0)
    {
        pop(stack);
    }
    free(stack);
}

int hamilton_distance(int x, int y, int x_dest, int y_dest)
{
    return abs(x - x_dest) + abs(y - y_dest);
}

 bfs (board_t *board, int x_orig, int y_orig, int x_dest, int y_dest)
{
    //Se crea el nodo origen
    bfs_node *node_orig = (bfs_node *)malloc(sizeof(bfs_node));
    node_orig->x = x_orig;
    node_orig->y = y_orig;
}

typedef struct {
    int count;
    struct stack_node *head;
    struct stack_node *tail;
} queue_t;

queue_t *create_queue()
{
    queue_t *queue = (queue_t *)malloc(sizeof(queue_t));
    queue->count = 0;
    queue->head = NULL;
    queue->tail = NULL;
    return queue;
}


void enqueue(queue_t *queue, node_t *node)
{
    if (queue->count == 0)
    {
        queue->head = node;
        queue->tail = node;
        queue->count++;
    }
    else
    {
        queue->tail->next = node;
        queue->tail = node;
        queue->count++;
    }
}

node_t *dequeue(queue_t *queue)
{
    if (queue->count == 0)
    {
        printf("Queue is empty\n");
        return NULL;
    }
    else
    {
        node_t *node = queue->head;
        queue->head = queue->head->next;
        queue->count--;
        return node;
    }
}

void destroy_queue(queue_t * q)
{
    while(q->count > 0)
    {
        node_t *c = dequeue(q);
        free(c);
    }
    free(q);
}


stack_t bfs(board_t *board, int x_orig, int y_orig, int x_dest, int y_dest)
{
    bool visited[board->width][board->height];
    for (int i = 0; i < board->width; i++)
    {
        for (int j = 0; j < board->height; j++)
        {
            visited[i][j] = false;
        }
    }

    // queue_t *path = create_queue();
    queue_t *to_proccess = create_queue();

    node_t *node_orig = (node_t *)malloc(sizeof(node_t));
    node_orig->x = x_orig;
    node_orig->y = y_orig;
    node_orig->d = 0;
    node_orig->parent = NULL;
    visited[x_orig][y_orig] = true;
    enqueue(to_proccess, node_orig);

    while(to_proccess->count > 0)
    {
        node_t *node = dequeue(to_proccess);

        if (get_cell_state(board, node->x, node->y) == FOOD ) {
            // reverse node tree
            node_t *current = node;
            stack_t path;
            path.count = 0;
            path.top = NULL;
            while (current->parent != NULL)
            {
                push(&path, current);
                current = current->parent;
            }
            
            return path;
        }

        point_t possible_moves[4];
        get_possible_moves(node->x, node->y, board, possible_moves);
        for (int i = 0; i < 4; i++)
        {
            // node_t *next_to_path;
            if (!is_invalid_point(possible_moves[i]) && !visited[possible_moves[i].y][possible_moves[i].x] )
            {
                node_t *node_new = (node_t *)malloc(sizeof(node_t));
                node_new->x = possible_moves[i].x;
                node_new->y = possible_moves[i].y;
                node_new->d = node->d + 1;
                node_new->parent = node;
                visited[possible_moves[i].y][possible_moves[i].x] = true;
                enqueue(to_proccess, node_new);
            }
        }
    }
    return (stack_t){};
}