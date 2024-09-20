#ifndef POLYGON_H
#define POLYGON_H

#include <cassert>
#include <vector>
#include <iostream>
#include <iterator>
#include <fstream>
#include <string>
#include <sstream>
#include <functional>
#include <algorithm>
#include <cctype>
#include <numeric>
#include <cmath>
#include <iomanip>

struct DelimiterIO {
    char exp;
};

struct IntIO {
    int& ref;
};

struct Point {
    int x, y;

    bool operator ==(const Point& other) const {
        return (x == other.x && y == other.y);
    }
};

struct Polygon {
    std::vector< Point > points;

    bool operator ==(const Polygon& other) const {
        return (points == other.points);
    }
};

std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
std::istream& operator>>(std::istream& in, IntIO&& dest);
std::istream& operator>>(std::istream& in, Polygon& dest);
std::ostream& operator<<(std::ostream& out, const Point& dest);
std::ostream& operator<<(std::ostream& out, const Polygon& dest);

#endif
