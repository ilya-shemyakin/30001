
#ifndef T3_POLYGON_H
#define T3_POLYGON_H
#include "Point.h"
#include <vector>
struct Polygon
{
    std::vector< Point > points_;
    double getArea() const;
};
std::istream& operator>>(std::istream& in, Polygon& polygon);
bool isEven(const Polygon& polygon);
bool isOdd(const Polygon& polygon);
bool compareAreas(const Polygon& firstObject, const Polygon& secondObject);
bool compareVertexesArea(const Polygon& firstObject, const Polygon& secondObject);
bool isIntersectionChecks(const Polygon& firstObject, const Polygon& secondObject);
struct PolygonsArea
{
    double area_;
    void operator()(const Polygon& plg);
};
struct TriangleArea
{
    double area_;
    Point p1_;
    const Point& operator()(const Point& p2, const Point& p3);
};
struct EqualFigures
{
    Polygon poly;
    bool operator()(const Polygon & firstObject, const Polygon & secondObject);
};
#endif
