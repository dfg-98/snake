#include "stack.h"

#include <stdlib.h>

stack_t *stack_create()
{
    stack_t *stack = (stack_t *)malloc(sizeof(stack_t));
    stack->top = NULL;
    stack->count = 0;
    return stack;
}

void stack_destroy(stack_t *stack)
{
    while (stack->top != NULL)
    {
        pop(stack);
    }
    free(stack);
}

// Push on the stack
void push(stack_t *stack, point_t point)
{
    if (stack->top == NULL)
    {
        stack->top = (snode_t *)malloc(sizeof(snode_t));
        stack->top->p = point;
        stack->top->next = NULL;
    }
    else
    {
        snode_t *node = (snode_t *)malloc(sizeof(snode_t));
        node->p = point;
        node->next = stack->top;
        stack->top = node;
    }
    stack->count++;
}

point_t pop(stack_t *stack)
{
    if (stack->top == NULL)
    {
        return (point_t){-1, -1};
    }
    point_t p = stack->top->p;
    snode_t *node = stack->top;
    stack->top = stack->top->next;
    stack->count--;
    free(node);
    return p;
}

point_t top(stack_t *stack)
{
    if (stack->top == NULL)
    {
        return (point_t){-1, -1};
    }
    return stack->top->p;
}
