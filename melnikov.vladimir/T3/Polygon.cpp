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
            //std::cout << "DELIM EXP: " << dest.exp << " GOT : " << c << '\n';
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
        if (in.peek() != '(')
        {
            in.setstate(std::ios::eofbit);
        }

        return in >> DelimiterIO{ '(' } >> dest.x >> DelimiterIO{ ';' }
        >> dest.y >> DelimiterIO{ ')' };
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
            in.setstate(std::ios::failbit);
            return in;
        }
        std::vector < Point > temp{};
        std::copy(std::istream_iterator< Point >(in), std::istream_iterator< Point >(),
                std::back_inserter(temp));
        if (temp.size() == size)
        {
            dest.points = temp;
            //std::cout << temp.size() << " " << dest.points.size() << " DONE \n";
        }
        if (in.eof())
        {
            in.clear();
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
            return (p1.y >= p2.y);
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
