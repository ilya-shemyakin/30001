#include "Polygon.h"

namespace melnikov
{
    std::istream &operator>>(std::istream &in, Polygon &dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        size_t size = 0;
        in >> size;
        dest.points.clear();
        std::copy_n(std::istream_iterator< Point >(in), size, std::back_inserter(dest.points));
        if (!in)
        {
            in.clear();
            in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
        }
        return in;
    }
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

}
