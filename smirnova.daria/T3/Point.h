#ifndef T3_POINT_H
#define T3_POINT_H
#include <iostream>
struct Point
{
    int x,y;
    bool operator==(const Point& object) const;
    bool operator<(const Point& object) const;
    bool operator<=(const Point& object) const;
    bool operator>=(const Point& object) const;

};
std::istream& operator>>(std::istream& in, Point& point);
#endif
