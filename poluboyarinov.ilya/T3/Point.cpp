#include "Point.h"
bool nspace::operator==(const Point& first, const Point& second)
{
    return (first.x == second.x && first.y == second.y);
}
