#ifndef MELNIKOV_VLADIMIR_COMMANDS_H
#define MELNIKOV_VLADIMIR_COMMANDS_H
#include "Polygon.h"
namespace melnikov
{
    double getArea (const Polygon& shape);
    int areaHelper(Point point1, Point point2);
}
#endif //MELNIKOV_VLADIMIR_COMMANDS_H
