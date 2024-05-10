#include "Commands.h"
#include <functional>
#include <cmath>
#include <numeric>
using namespace std::placeholders;
namespace melnikov
{
    int areaHelper(Point point1, Point point2)
    {
        return (point1.x * point2.y - point1.y * point2.x);
    }
    double getArea (const Polygon shape)
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
    double addArea (double area, const Polygon & shape)
    {
        return area += getArea(shape);
    }
    std::ostream & area(std::istream& in, std::ostream& out, std::vector< Polygon > & shapes)
    {
        std::string arg;
        in >> arg;
        if (arg == "ODD")
        {
            auto functor = std::bind(addArea, _1, _2);
            return out << std::accumulate(shapes.begin(), shapes.end(), 0.0, functor);
        }
        else if (arg == "EVEN")
        {

        }
        else if (arg == "MEAN")
        {

        }
        else
        {
            throw std::invalid_argument("Invvalid command argument");
        }
    }
}