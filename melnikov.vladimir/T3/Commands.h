#ifndef MELNIKOV_VLADIMIR_COMMANDS_H
#define MELNIKOV_VLADIMIR_COMMANDS_H
#include "Polygon.h"
#include <functional>

namespace melnikov
{
    double getArea (const Polygon& shape);
    int areaHelper(Point point1, Point point2);
    double addArea (double area, const Polygon & shape,
                    std::function< bool(const Polygon&) > exp);
    double addEveryArea (double area, const Polygon & shape);
    bool hasOddPoints(const Polygon& shape);
    bool hasEvenPoints(const Polygon& shape);
    bool hasNumOfPoints(const Polygon& shape, size_t size);
    bool isPermutation(const Polygon& shape1, const Polygon& shape2);
    double comparedArea(double area2, const Polygon & shape1,
                        std::function< double(double, double) > exp);
    size_t comparedVert(size_t vert1, const Polygon & shape1,
                        std::function< size_t(size_t, size_t ) > exp);
    std::ostream & area(std::istream& in, std::ostream& out,
                        std::vector< Polygon > & shapes);
    std::ostream & max(std::istream& in, std::ostream& out,
                       std::vector< Polygon > & shapes);
    std::ostream & min(std::istream& in, std::ostream& out,
                       std::vector< Polygon > & shapes);
    std::ostream & count(std::istream& in, std::ostream& out,
                       std::vector< Polygon > & shapes);
    size_t counter(size_t count, const Polygon& shape,
                   std::function< bool(const Polygon&) > exp);
    std::ostream & perms(std::istream& in, std::ostream& out,
                         std::vector< Polygon > & shapes);
}
#endif //MELNIKOV_VLADIMIR_COMMANDS_H
