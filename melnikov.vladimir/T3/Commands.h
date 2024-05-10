#ifndef MELNIKOV_VLADIMIR_COMMANDS_H
#define MELNIKOV_VLADIMIR_COMMANDS_H
#include "Polygon.h"
namespace melnikov
{
    double getArea (const Polygon shape);
    int areaHelper(Point point1, Point point2);
    double addArea (double area, const Polygon & shape);
    std::ostream & area(std::istream& in, std::ostream& out, std::vector< Polygon > & shapes);
}
#endif //MELNIKOV_VLADIMIR_COMMANDS_H
