#ifndef _POLYGON_H
#define _POLYGON_H

#include <iostream>
#include <string>
#include <iterator>
#include <vector>
#include <limits>
#include <sstream>
#include <map>

struct Point {
    int x;
    int y;

    bool operator ==(const Point& other) const
    {
        return ((other.x == this->x) && (other.y == this->y));
    }
};

struct Polygon {
    std::vector< Point > points;

    bool operator==(const Polygon& other) const
    {
        if (this->points.size() != other.points.size()) {
            return false;
        }
        for (size_t i = 0; i < this->points.size(); i++) {
            if (!(this->points[i] == other.points[i])) {
                return false;
            }
        }
        return true;
    }
};

struct DelimiterIO {
    char exp;
};

struct intIO {
    int& ref;
};

struct DelStrIO {
    std::string exp;
};

class iofmtguard {
public:
    iofmtguard(std::basic_ios<char>& s) noexcept;
    ~iofmtguard();

private:
    std::basic_ios<char>& s_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios<char>::fmtflags fmt_;
};

std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
std::istream& operator>>(std::istream& in, intIO&& dest);
std::istream& operator>>(std::istream& in, Polygon& dest);

#endif
