#include "Commands.h"
#include <functional>
#include <cmath>

using namespace std::literals;
namespace melnikov
{
    int areaHelper(Point point1, Point point2)
    {
        return (point1.x * point2.y - point1.y * point2.x);
    }
    double getArea (const Polygon& shape)
    {
        size_t size = shape.points.size();
        double area = 0.0;
        for (auto i = shape.points.begin(); i != --shape.points.end(); i++)
        {
            area += areaHelper(*i, *std::next(i));
        }
        area += areaHelper(shape.points[size-1], shape.points[0]);
        return std::fabs(area/2.0);
    }
}