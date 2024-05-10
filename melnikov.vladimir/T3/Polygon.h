#ifndef MELNIKOV_VLADIMIR_POLYGON_H
#define MELNIKOV_VLADIMIR_POLYGON_H
#include <vector>
#include <ios>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <limits>
namespace melnikov
{
    struct Point
    {
        int x, y;
    };
    struct Polygon
    {
        std::vector< Point > points;
    };
    struct DelimiterIO
    {
        char exp;
    };
    std::istream &operator >>(std::istream & in, Point& dest);
    std::istream &operator >>(std::istream & in, Polygon& dest);
    std::istream &operator >>(std::istream &in, DelimiterIO &&dest);
    template < class T >
    T maxOfTwo(T x, T y)
    {
        return (x > y ? x : y);
    }
    template < class T >
    T minOfTwo(T x, T y)
    {
        return (x < y ? x : y);
    }
    bool operator >(const Point& p1, const Point& p2);
    bool operator ==(const Point& p1, const Point& p2);
    bool operator ==(const Polygon& p1, const Polygon& p2);

}
#endif //MELNIKOV_VLADIMIR_POLYGON_H
