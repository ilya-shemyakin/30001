#include "Commands.h"
#include <cmath>
#include <numeric>
#include <functional>
#include <iomanip>
#include <algorithm>
using namespace std::placeholders;
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
    double addArea (double area, const Polygon & shape, std::function< bool(const Polygon&) > exp)
    {
        return area += (exp(shape) ? getArea(shape) : 0);
    }
    double addEveryArea (double area, const Polygon & shape)
    {
        return area += getArea(shape);
    }
    bool hasOddPoints(const Polygon& shape)
    {
        return shape.points.size() % 2 != 0;
    }
    bool hasEvenPoints(const Polygon& shape)
    {
        return !hasOddPoints(shape);
    }
    bool hasNumOfPoints(const Polygon& shape, size_t size)
    {
        return shape.points.size() == size;
    }
    size_t counter(size_t count, const Polygon& shape, std::function< bool(const Polygon&) > exp)
    {
        return (exp(shape) ? ++count : count);
    }
    std::ostream & area(std::istream& in, std::ostream& out, std::vector< Polygon > & shapes)
    {
        out << std::fixed << std::setprecision(1);
        std::string arg;
        in >> arg;
        if (arg == "ODD")
        {
            auto functor = std::bind(addArea, _1, _2, hasOddPoints);
            return out << std::accumulate(shapes.begin(), shapes.end(), 0.0, functor) << '\n';
        }
        else if (arg == "EVEN")
        {
            auto functor = std::bind(addArea, _1, _2, hasEvenPoints);
            return out << std::accumulate(shapes.begin(), shapes.end(), 0.0, functor) << '\n';
        }
        else if (arg == "MEAN")
        {
            if (shapes.size() == 0)
            {
                throw std::invalid_argument("");
            }
            auto functor = std::bind(addEveryArea, _1, _2);
            return out << std::accumulate(shapes.begin(), shapes.end(),
                                          0.0, functor)/shapes.size() << '\n';
        }
        else
        {
            size_t size = std::stoull(arg);
            if(size <= 2)
            {
                throw std::invalid_argument("");
            }
            std::function< bool(const Polygon&) > temp = std::bind(hasNumOfPoints, _1, size);
            auto functor = std::bind(addArea, _1, _2, temp);
            return out << std::accumulate(shapes.begin(), shapes.end(), 0.0, functor) << '\n';
        }
    }
    double comparedArea(double area2, const Polygon & shape1,
                        std::function< double(double, double ) > exp)
    {
        return exp(getArea(shape1), area2);
    }
    size_t comparedVert(size_t vert1, const Polygon & shape1,
                        std::function< size_t(size_t, size_t ) > exp)
    {
        return exp(shape1.points.size(), vert1);
    }

    std::ostream & max(std::istream& in, std::ostream& out,
                       std::vector< Polygon > & shapes)
    {
        std::string arg;
        in >> arg;

        if (!shapes.empty() && arg == "AREA")
        {
            out << std::fixed << std::setprecision(1);
            auto functor = std::bind(comparedArea, _1, _2, maxOfTwo < double >);
            return out << std::accumulate(shapes.begin(), shapes.end(),
                                          0.0, functor) << '\n';
        }
        else if (!shapes.empty() && arg == "VERTEXES")
        {
            auto functor = std::bind(comparedVert, _1, _2, maxOfTwo < size_t >);
            return out << std::accumulate(shapes.begin(), shapes.end(),
                                          3, functor) << '\n';
        }
        else
        {
            throw std::invalid_argument("");
        }
    }
    std::ostream & min(std::istream& in, std::ostream& out,
                       std::vector< Polygon > & shapes)
    {
        std::string arg;
        in >> arg;

        if (!shapes.empty() && arg == "AREA")
        {
            out << std::fixed << std::setprecision(1);
            auto functor = std::bind(comparedArea, _1, _2, minOfTwo < double >);
            return out << std::accumulate(shapes.begin(), shapes.end(),
                                          getArea(shapes[0]), functor) << '\n';
        }
        else if (!shapes.empty() && arg == "VERTEXES")
        {
            auto functor = std::bind(comparedVert, _1, _2, minOfTwo < size_t >);
            return out << std::accumulate(shapes.begin(), shapes.end(),
                                          shapes[0].points.size(), functor) << '\n';
        }
        else
        {
            throw std::invalid_argument("");
        }
    }
    std::ostream & count(std::istream& in, std::ostream& out,
                         std::vector< Polygon > & shapes)
    {
        std::string arg;
        in >> arg;
        if (arg == "ODD")
        {
            auto functor = std::bind(counter, _1, _2, hasOddPoints);
            return out << std::accumulate(shapes.begin(), shapes.end(), 0, functor) << '\n';
        }
        else if (arg == "EVEN")
        {

            auto functor = std::bind(counter, _1, _2, hasEvenPoints);
            return out << std::accumulate(shapes.begin(), shapes.end(), 0, functor) << '\n';
        }
        else
        {
            size_t size = std::stoull(arg);
            if(size <= 2)
            {
                throw std::invalid_argument("");
            }
            std::function< bool(const Polygon&) > temp = std::bind(hasNumOfPoints, _1, size);
            auto functor = std::bind(counter, _1, _2, temp);
            return out << std::accumulate(shapes.begin(), shapes.end(), 0, functor) << '\n';
        }
    }
    bool comparatorPoint (const Point& p1, const Point& p2)
    {
        if (p1.x != p2.x)
        {
            return (p1.x > p2.x);
        }
        else
        {
            return (p1.y >= p2.y);
        }
    }

    bool isPermutation(const Polygon& shape1, const Polygon& shape2)
    {
        if (shape1.points.size() != shape2.points.size())
        {
            return false;
        }
        std::vector< Point > temp1 = shape1.points;
        std::vector< Point > temp2 = shape2.points;
        std::sort(temp1.begin(), temp1.end(), comparatorPoint);
        std::sort(temp2.begin(), temp2.end(), comparatorPoint);
        return temp1 == temp2;
    }
    std::ostream & perms(std::istream& in, std::ostream& out,
                         std::vector< Polygon > & shapes) {
        Polygon arg;
        in >> arg;
        if (in.fail())
        {
            throw std::invalid_argument("");
        }
        else
        {
            std::function< bool(const Polygon&) > temp = std::bind(isPermutation, _1, arg);
            auto functor = std::bind(counter, _1, _2,temp);
            return out << std::accumulate(shapes.begin(), shapes.end(), 0, functor) << '\n';
        }
    }
    bool toCount(const Polygon& current, const Polygon& arg)
    {
        return arg==current;
    }
    size_t inOrderCount(size_t maxCount, size_t& currentCount, const Polygon& current,
                        std::function<bool (const Polygon&)> exp)
    {
        currentCount = (exp(current) ? (currentCount+1) : 0);
        maxCount = maxOfTwo(currentCount, maxCount);
        return maxCount;
    }
    std::ostream & maxSeq(std::istream& in, std::ostream& out,
                          std::vector< Polygon > & shapes)
    {
        Polygon arg;
        in >> arg;
        if (in.fail())
        {
            throw std::invalid_argument("");
        }

        size_t currentCount = 0;
        std::function< bool(const Polygon&) > temp = std::bind(toCount, _1, arg);
        auto functor = std::bind(inOrderCount, _1, currentCount , _2, temp);
        size_t res = std::accumulate(shapes.begin(), shapes.end(), 0, functor);
        return out << res << '\n';
    }
}
