#ifndef POLYGON_H
#define POLYGON_H

#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <iterator>
#include <vector>
#include <iomanip>
#include <algorithm>

#include "Point.h"

namespace nspace
{
    struct Polygon
    {
        std::vector< Point > points;
        double getArea()
        {
            double result = 0.0;
            for (long unsigned int i = 0; i < points.size() - 1; i++)
            {
                result += (points[i].x * points[i + 1].y);
                result -= (points[i].y * points[i + 1].x);
            }
            result += (points[points.size() - 1].x * points[0].y);
            result -= (points[0].x * points[points.size() - 1].y);
            result /= 2;
            return abs(result);
        }
    };
    struct DelimiterIO
    {
        char exp;
    };
    struct IntIO
    {
        int& ref;
    };
    class iofmtguard
    {
    public:
        iofmtguard(std::basic_ios< char >& s);
        ~iofmtguard();
    private:
        std::basic_ios< char >& s_;
        char fill_;
        std::streamsize precision_;
        std::basic_ios< char >::fmtflags fmt_;
    };
    std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
    std::istream& operator>>(std::istream& in, IntIO&& dest);
    std::istream& operator>>(std::istream& in, Polygon& dest);

    bool operator==(const Polygon& first, const Polygon& second);
}
#endif
