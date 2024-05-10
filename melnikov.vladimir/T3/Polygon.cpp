#include "Polygon.h"

namespace melnikov
{

    std::istream &operator>>(std::istream &in, DelimiterIO &&dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        char c = '0';
        in >> c;
        if (in && c != dest.exp)
        {
            in.setstate(std::ios::failbit);
        }
        return in;
    }
    std::istream &operator>>(std::istream &in, Point &dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        in >> DelimiterIO{ '(' } >> dest.x >> DelimiterIO{ ';' }
        >> dest.y >> DelimiterIO{ ')' };
        return in;
    }
    std::istream &operator>>(std::istream &in, Polygon &dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        size_t size = 0;
        in >> size;
        if (size < 3)
        {
            in.clear();
            in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
            return in;
        }
        dest.points.clear();
        std::copy_n(std::istream_iterator< Point >(in), size, std::back_inserter(dest.points));
        if (!in)
        {
            in.clear();
            in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
        }
        return in;
    }
    bool operator >(const Point& p1, const Point& p2)
    {
        if (p1.x > p2.x)
        {
            return true;
        }
        else if (p1.x < p2.x)
        {
            return false;
        }
        else
        {
            return p1.y >= p2.y;
        }
    }
    bool operator ==(const Point& p1, const Point& p2)
    {
        return (p1.x == p2.x && p1.y == p2.y);
    }
    bool operator ==(const Polygon& p1, const Polygon& p2)
    {
        return p1.points == p2.points;
    }

}
