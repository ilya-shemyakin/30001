#ifndef POINT_H
#define POINT_H

namespace nspace
{
    struct Point
    {
        int x, y;
    };
    bool operator==(const Point& first, const Point& second);
}

#endif
