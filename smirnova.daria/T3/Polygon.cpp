#include "Polygon.h"
#include "commandOfFigure.h"
#include <numeric>
#include <iterator>
#include <cmath>
#include <algorithm>
#include <iostream>

std::istream& operator>>(std::istream& input, Polygon& dest)
{
    std::istream::sentry guard(input);
    if (!guard)
    {
        return input;
    }
    Polygon polygon;
    size_t vertexes;
    if (!(input >> vertexes) || vertexes < 3)
    {
        input.setstate(std::ios::failbit);
    }
    using input_it_t = std::istream_iterator< Point >;
    std::vector< Point > points;
    std::copy_n(input_it_t{ input }, vertexes, std::back_inserter(points));
    if (input)
    {
        polygon.points_ = std::move(points);
    }
    if (input && vertexes == polygon.points_.size())
    {
        dest = polygon;
    }
    else
    {
        input.setstate(std::ios::failbit);
    }
    return input;
}
bool operator==(const Polygon& first, const Polygon& second)
{
    if (first.points_.size() != second.points_.size())
    {
        return false;
    }
    else
    {
        return std::equal(first.points_.cbegin(), first.points_.cend(), second.points_.cbegin());
    }
}

bool equalPolygons(const Polygon& firstObject, const Polygon& secondObject)
{
    if (firstObject.points_.size() != secondObject.points_.size())
    {
        return false;
    } else {
        return std::equal(firstObject.points_.cbegin(),
                          firstObject.points_.cend(), secondObject.points_.cbegin());
    }
}

bool compareArea(const Polygon& lhs, const Polygon& rhs)
{
    return plusArea(0,lhs) < plusArea(0,rhs);
}

bool equalPolygons(const Polygon& firstObject, const Polygon& secondObject)
{
    if (firstObject.points_.size() != secondObject.points_.size())
    {
        return false;
    } else {
        return std::equal(firstObject.points_.cbegin(),
                          firstObject.points_.cend(), secondObject.points_.cbegin());
    }
}
bool isIntersectionChecks(const Polygon& firstObject, const Polygon& secondObject)
{
    Point minfirstObject = *std::min_element(firstObject.points_.cbegin(), firstObject.points_.cend());
    Point maxfirstObject = *std::max_element(firstObject.points_.cbegin(), firstObject.points_.cend());
    Point minsecondObject = *std::min_element(secondObject.points_.cbegin(), secondObject.points_.cend());
    Point maxsecondObject = *std::max_element(secondObject.points_.cbegin(), secondObject.points_.cend());
    return ((maxfirstObject >= minsecondObject) and (minfirstObject <= maxsecondObject)) or
           ((minsecondObject <= maxfirstObject) and (maxsecondObject >= minfirstObject));
}
