#ifndef POLYGON_H
#define POLYGON_H

#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <sstream>

#include "Iofmtguard.h"

struct Point
{
    int x;
    int y;

    bool operator ==(const Point& other) const;
};

struct Polygon
{
    std::vector< Point > vertexes;

    bool operator==(const Polygon& other) const;
};

struct DelimiterIO
{
    char exp;
};

struct intIO
{
    int& ref;
};

struct DelStrIO
{
    std::string exp;
};

std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
std::istream& operator>>(std::istream& in, intIO&& dest);
std::istream& operator>>(std::istream& in, Point& dest);
std::istream& operator>>(std::istream& in, Polygon& dest);

std::ostream& operator<<(std::ostream& ost, const Point& point);
std::ostream& operator<<(std::ostream& ost, const Polygon& polygon);

#endif