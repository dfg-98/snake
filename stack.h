#ifndef __STACK_H__
#define __STACK_H__

#include "typedef.h"

typedef struct snode
{
    point_t p;
    struct snode *next;
} snode_t;


typedef struct 
{
    int count;
    snode_t *top;
}stack_t;

stack_t *stack_create();
void stack_destroy(stack_t *stack);
void push(stack_t *stack, point_t p);
point_t pop(stack_t *stack);
point_t top(stack_t *stack);




#endif