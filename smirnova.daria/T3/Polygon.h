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
struct EqualFigures
{
    Polygon poly;
    bool operator()(const Polygon & firstObject, const Polygon & secondObject);
};
#endif
