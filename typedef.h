#ifndef __TYPEDEF_H__
#define __TYPEDEF_H__

#include <stdbool.h>

typedef unsigned int uint;

typedef struct {
    int x;
    int y;
} point_t;

point_t create_point(int x, int y);

bool is_invalid_point(point_t p);
#endif