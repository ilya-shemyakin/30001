#include "Polygon.h"
#include "commandOfFigure.h"
#include <numeric>
#include <iterator>
#include <cmath>
#include <algorithm>
#include <iostream>

std::istream& operator>>(std::istream& input, Polygon& dest)
{
    std::istream::sentry sentry(input);
    if (!sentry)
    {
        return input;
    }
    Polygon polygon;
    size_t vertexes; //вершина
    if (!(input >> vertexes) || vertexes < 3)
    {
        input.setstate(std::ios::failbit);
    }
    using input_it_t = std::istream_iterator< Point >;
    std::vector< Point > points;
    std::copy_n(input_it_t{ input }, vertexes, std::back_inserter(points));
    //Возвращает итератор, используемый для вставки элементов в конце указанной коллекции
    if (input)
    {
        polygon.points_ = std::move(points);
    }
    if (input and vertexes == polygon.points_.size())
    {
        dest = polygon;
    }
    else
    {
        input.setstate(std::ios::failbit);
    }
    return input;
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
bool EqualFigures::operator()(const Polygon& firstObject, const Polygon& secondObject)
{
    return equalPolygons(firstObject,secondObject);
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
