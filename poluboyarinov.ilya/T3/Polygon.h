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

namespace nspace
{
    struct Point
    {
        int x, y;

    };
    struct Polygon
    {
        std::vector< Point > points;
        
        double getArea()
        {
            double result = 0.0;
            for (int i = 0; i < points.size() - 1; i++)
            {
                Point p1 = points[i];
                Point p2 = points[i + 1];
                result += (points[i].x * points[i + 1].y);
                result -= (points[i].y * points[i + 1].x);
            }
            result += (points[points.size() - 1].x * points[0].y);
            result -= (points[0].x * points[points.size() - 1].y);
            result /= 2;
            return abs(result);
        }

        bool operator==(const Polygon& other) const
        {
            if (points.size() != other.points.size())
            {
                return false;
            }
            else
            {
                bool result = true;
                for (int i = 0; i < this->points.size(); i++)
                {
                    if (this->points[i].x != other.points[i].x || this->points[i].y != other.points[i].y)
                    {
                        result = false;
                    }
                }
                return result;
            }
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
}
#endif
