#include "Polygon.h"
#include "commandOfFigure.h"
#include <numeric>
#include <iterator>
#include <cmath>
#include <algorithm>
#include <iostream>

std::istream& operator>>(std::istream& in, Polygon& polygon)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    size_t counter = 0;
    in >> counter;
    if (counter <= 2)
    {
        in.setstate(std::ios::failbit);
        return in;
    }
    std::vector< Point > temp;
    temp.reserve(counter);
    using input_it_t = std::istream_iterator< Point >;
    std::copy_n(input_it_t{ in }, counter, std::back_inserter(temp));
    if (in and temp.size() == counter)
    {
        polygon.points_ = temp;
    }
    return in;
}

//double Polygon::getArea() const
//{
//    using namespace std::placeholders;
//    auto accumulateArea = std::bind(PolygonArea{ points_.at(1) }, _1, _2, points_.at(0));
//    return std::accumulate(points_.cbegin(), points_.cend(), 0.0, accumulateArea) / 2; //ср знач
//}

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
const Point& TriangleArea::operator()(const Point& p2, const Point& p3)
{
    double a = getLength(p1_, p2);
    double b = getLength(p2, p3);
    double c = getLength(p1_, p3);
    const double TWO = 2.0;
    double p = (a + b + c) / TWO;
    area_ += sqrt(p * (p - a) * (p - b) * (p - c));
    return p3;
}
double getPolygonArea(const Polygon& polygon)
{
    TriangleArea accArea{ 0.0, polygon.points_[0] };
    std::accumulate(polygon.points_.begin() + 2, polygon.points_.end(), polygon.points_[1], std::ref(accArea));
    return accArea.area_;
}
void PolygonsArea::operator()(const Polygon& polygon)
{
    area_ += getPolygonArea(polygon);
}

bool isEven(const Polygon& plg) //попробовать объединить
{
    return ((plg.points_.size() % 2) == 0);
}

bool isOdd(const Polygon& plg)
{
    return ((plg.points_.size() % 2) == 1);
}

bool compareVertexesArea(const Polygon& firstObject, const Polygon& secondObject)
{
    return firstObject.points_.size() < secondObject.points_.size();
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
