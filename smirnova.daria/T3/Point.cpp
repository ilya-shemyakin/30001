#include "Point.h"
#include <algorithm>
#include <functional>
#include <iterator>
#include <numeric>
#include <cmath>
#include "Delimeter.h"
std::istream& operator>>(std::istream& in, Point& point)
{
    std::istream::sentry guard(in);
    if (!guard)
    {
        return in;
    }
    using del = Delimiter;
    Point temp{ 0, 0 };
    in >> del{ '(' } >> temp.x >> del{ ';' } >> temp.y >> del{ ')' };
    if (in)
    {
        point = temp;
    }
    return in;
}

bool Point::operator==(const Point& object) const
{
    return (x == object.x) && (y == object.y);
}

bool Point::operator<(const Point& object) const
{
    return (x < object.x and y < object.y);
}

bool Point::operator<=(const Point& object) const
{
    return (*this <= object);
}

bool Point::operator>=(const Point& object) const
{
    return !(*this < object);
}
double getLength(const Point& p1, const Point& p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}
