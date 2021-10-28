#include "typedef.h"

point_t create_point(int x, int y)
{
    point_t p;
    p.x = x;
    p.y = y;
    return p;
}

bool is_invalid_point(point_t p)
{
    return p.x < 0 || p.y < 0;
}
