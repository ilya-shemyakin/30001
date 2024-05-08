#ifndef MELNIKOV_VLADIMIR_POLYGON_H
#define MELNIKOV_VLADIMIR_POLYGON_H
#include <vector>
#include <ios>

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
    std::istream &operator <<(std::istream & in, Point& dest);
    std::istream &operator <<(std::istream & in, Polygon& dest);
    std::istream &operator>>(std::istream &in, DelimiterIO &&dest);
}
#endif //MELNIKOV_VLADIMIR_POLYGON_H
