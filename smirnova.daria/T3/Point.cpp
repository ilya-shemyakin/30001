#include "Point.h"
#include <algorithm>
#include <functional>
#include <iterator>
#include <numeric>
#include <cmath>
#include "Delimeter.h"
std::istream& operator>>(std::istream& in, Point& point)
{
    std::istream::sentry sentry(in);
    if (!sentry)
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
    return (x == object.x) and (y == object.y);
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
