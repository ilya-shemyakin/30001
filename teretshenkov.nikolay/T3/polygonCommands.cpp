#include "polygonCommands.h"

using namespace std::placeholders;

int getGaussMultiplication(const Point &p1, const Point &p2)
{
    return (p1.x * p2.y - p1.y * p2.x);
}

double getArea(const Polygon& polygon)
{
    double area = 0.0;

    for (auto i = polygon.points.begin(); i != (polygon.points.end() - 1); i++)
    {
        area += getGaussMultiplication(*i, *(i + 1));
    }

    area += getGaussMultiplication(polygon.points.back(), polygon.points.front());

    return std::fabs(area / 2.0);
}

double addArea(double area, const Polygon& polygon, std::function< bool(const Polygon&) > foo)
{
    if (foo(polygon))
    {
        area += getArea(polygon);
    }
    return area;
}

bool isNumPointsOdd(const Polygon& polygon)
{
    return polygon.points.size() % 2 != 0;
}

bool isNumPointsEven(const Polygon& polygon)
{
    return polygon.points.size() % 2 == 0;
}

bool isNumPointsCertain(const Polygon& polygon, size_t size)
{
    return polygon.points.size() == size;
}


double addAreaCommon(double area, const Polygon& polygon)
{
    area += getArea(polygon);
    return area;
}


std::ostream& area(std::istream& in, std::ostream& out,
    std::vector< Polygon >& polygons)
{
    std::string mode;
    in >> mode;
    out << std::fixed << std::setprecision(1);
    if (mode == "EVEN")//чётный
    {
        auto functor = std::bind(addArea, _1, _2, isNumPointsEven);
        return out << std::accumulate(polygons.begin(), polygons.end(), 0.0, functor) << '\n';
    }
    else if (mode == "ODD")
    {
        auto functor = std::bind(addArea, _1, _2, isNumPointsOdd);
        return out << std::accumulate(polygons.begin(), polygons.end(), 0.0, functor) << '\n';
    }
    else if (mode == "MEAN")
    {
        if (polygons.size() == 0)
        {
            throw std::invalid_argument("WRONG SIZE");
        }
        auto functor = std::bind(addAreaCommon, _1, _2);
        return out << std::accumulate(
            polygons.begin(), polygons.end(), 0.0, functor) / polygons.size() << '\n';
    }
    else
    {
        size_t size = std::stoull(mode);
        if (size <= 2)
        {
            throw std::invalid_argument("WRONG SIZE");
        }
        std::function< bool(const Polygon&) > temp = std::bind(isNumPointsCertain, _1, size);
        auto functor = std::bind(addArea, _1, _2, temp);
        return out << std::accumulate(polygons.begin(), polygons.end(), 0.0, functor) << '\n';
    }
}

double compareArea(double area2, const Polygon& polygon1, bool isLess)
{
    double area1 = getArea(polygon1);
    if (isLess)
    {
        return ((area1 < area2) ? area1 : area2);
    }
    return ((area1 > area2) ? area1 : area2);
}

size_t compareVert(size_t size2, const Polygon& polygon1, bool isLess)
{
    size_t size1 = polygon1.points.size();
    if (isLess)
    {
        return ((size1 < size2) ? size1 : size2);
    }
    return ((size1 > size2) ? size1 : size2);
}

std::ostream& max(std::istream& in, std::ostream& out,
    std::vector< Polygon >& polygons)
{
    std::string mode;
    in >> mode;

    if (!polygons.empty() && mode == "AREA")
    {
        out << std::fixed << std::setprecision(1);
        auto functorArea = std::bind(compareArea, _1, _2, false);
        return out << std::accumulate(polygons.begin(), polygons.end(), 0.0, functorArea) << '\n';
    }
    else if (!polygons.empty() && mode == "VERTEXES")
    {
        auto functorVert = std::bind(compareVert, _1, _2, false);
        return out << std::accumulate(polygons.begin(), polygons.end(), 3, functorVert) << '\n';
    }
    else
    {
        throw std::invalid_argument("WRONG MODE");
    }
}

std::ostream& min(std::istream& in, std::ostream& out,
    std::vector< Polygon >& polygons)
{
    std::string mode;
    in >> mode;

    if (!polygons.empty() && mode == "AREA")
    {
        out << std::fixed << std::setprecision(1);
        auto functor = std::bind(compareArea, _1, _2, true);
        return out << std::accumulate(
            polygons.begin(), polygons.end(), getArea(polygons[0]), functor) << '\n';
    }
    else if (!polygons.empty() && mode == "VERTEXES")
    {
        auto functor = std::bind(compareVert, _1, _2, true);
        return out << std::accumulate(
            polygons.begin(), polygons.end(), polygons[0].points.size(), functor) << '\n';
    }
    else
    {
        throw std::invalid_argument("WRONG MODE");
    }
}

size_t counter(size_t count, const Polygon& polygon, std::function< bool(const Polygon&) > foo)
{
    if (foo(polygon))
    {
        ++count;
    }
    return count;
}

std::ostream& count(std::istream& in, std::ostream& out,
    std::vector< Polygon >& polygons)
{
    std::string mode;
    in >> mode;

    if (mode == "EVEN")
    {
        auto functor = std::bind(counter, _1, _2, isNumPointsEven);
        return out << std::accumulate(polygons.begin(), polygons.end(), 0, functor) << '\n';
    }
    else if (mode == "ODD")
    {
        auto functor = std::bind(counter, _1, _2, isNumPointsOdd);
        return out << std::accumulate(polygons.begin(), polygons.end(), 0, functor) << '\n';
    }
    else
    {
        int size = std::stoi(mode);
        if (size <= 2)
        {
            throw std::invalid_argument("WRONG SIZE");
        }

        std::function< bool(const Polygon&) > tempF = std::bind(isNumPointsCertain, _1, size);
        auto functor = std::bind(counter, _1, _2, tempF);
        return out << std::accumulate(polygons.begin(), polygons.end(), 0, functor) << '\n';
    }
}

bool comparePoints(const Point& point1, const Point& point2)
{
    if (point1.x != point2.x)
    {
        return (point1.x > point2.x);
    }
    else
    {
        return (point1.y >= point2.y);
    }
}

bool isCoordPermutation(const Polygon& polygon1, const Polygon& polygon2)
{
    if (polygon1.points.size() == polygon2.points.size())
    {
        std::vector< Point > points1 = polygon1.points;
        std::vector< Point > points2 = polygon2.points;
        std::sort(points1.begin(), points1.end(), comparePoints);
        std::sort(points2.begin(), points2.end(), comparePoints);
        return points1 == points2;
    }
    return false;
}

std::ostream& perms(std::istream& in, std::ostream& out,
    std::vector< Polygon >& polygons)
{
    Polygon local;
    in >> local;
    if (!in)
    {
        throw std::invalid_argument("FAILED");
    }
    else
    {
        std::function< bool(const Polygon&) > tempF = std::bind(isCoordPermutation, _1, local);
        auto functor = std::bind(counter, _1, _2, tempF);
        return out << std::accumulate(polygons.begin(), polygons.end(), 0, functor) << '\n';
        return out;
    }
}

double getDistance(const Point& point1, const Point& point2)
{
    return (sqrt(pow(point2.x - point1.x, 2) + pow(point2.y - point1.y, 2)));
}

bool isEqualDouble(double x, double y)
{
    return std::fabs(x - y) < pow(10, -5);//std::numeric_limits<double>::epsilon();
}

bool isRightAngledTriangle(const Point& point1, const Point& point2, const Point& point3)
{
    double a = getDistance(point1, point2);
    double b = getDistance(point2, point3);
    double c = getDistance(point1, point3);

    return (isEqualDouble(pow(c, 2), pow(a, 2) + pow(b, 2)) ||
        isEqualDouble(pow(a, 2), pow(b, 2) + pow(c, 2)) ||
        isEqualDouble(pow(b, 2), pow(c, 2) + pow(a, 2)));
}

bool hasRightAngle(const Polygon& polygon)
{
    size_t size = polygon.points.size();

    if (size <= 2)
    {
        throw std::invalid_argument("WRONG SIZE");
    }

    bool result = false;

    for (size_t i = 0; i < size && !result; ++i)
    {
        Point a = polygon.points[i];
        Point b = polygon.points[(i + 1) % size];
        Point c = polygon.points[(i + 2) % size];
        if (isRightAngledTriangle(a, b, c))
        {
            result = true;
        }
    }

    return result;
}

std::ostream& rightShapes(std::istream& in, std::ostream& out,
    std::vector< Polygon >& polygons)
{
    if (!in)
    {
        throw std::invalid_argument("FAILED");
    }
    std::function< bool(const Polygon&) > tempF = std::bind(hasRightAngle, _1);
    auto functor = std::bind(counter, _1, _2, tempF);
    return out << std::accumulate(polygons.begin(), polygons.end(), 0, functor) << '\n';
}
