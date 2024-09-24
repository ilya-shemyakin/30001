#ifndef T3_POLYGON_H
#define T3_POLYGON_H
#include "Point.h"
#include <vector>
struct Polygon
{
    std::vector< Point > points_;
};
std::istream& operator>>(std::istream& in, Polygon& polygon);
bool equalPolygons(const Polygon& firstObject, const Polygon& secondObject);
bool isIntersectionChecks(const Polygon& firstObject, const Polygon& secondObject);
bool equalPolygons(const Polygon& firstObject, const Polygon& secondObject);
bool compareArea(const Polygon& lhs, const Polygon& rhs);
bool operator==(const Polygon& first, const Polygon& second);
#endif
