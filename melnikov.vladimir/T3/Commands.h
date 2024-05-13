#ifndef MELNIKOV_VLADIMIR_COMMANDS_H
#define MELNIKOV_VLADIMIR_COMMANDS_H
#include "Polygon.h"
#include <functional>

namespace melnikov
{
    double getArea (const Polygon& shape);
    double areaHelper(const Point& point1, const Point& point2);
    double addArea (double area, const Polygon & shape,
                    std::function< bool(const Polygon&) > exp);
    double addEveryArea (double area, const Polygon & shape);
    bool hasOddPoints(const Polygon& shape);
    bool hasEvenPoints(const Polygon& shape);
    bool hasNumOfPoints(const Polygon& shape, size_t size);
    bool isPermutation(const Polygon& shape1, const Polygon& shape2);
    bool comparedArea(const Polygon & shape1, const Polygon & shape2);
    size_t comparedVert(const Polygon & shape1, const Polygon & shape2);
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
    std::ostream & maxSeq(std::istream& in, std::ostream& out,
                         std::vector< Polygon > & shapes);
    bool isNotEqual(const Polygon& current, const Polygon& arg);
}
#endif //MELNIKOV_VLADIMIR_COMMANDS_H
