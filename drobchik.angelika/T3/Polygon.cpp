#include "Polygon.h"

std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry) {
        return in;
    }
    char symb = '0';
    in >> symb;
    if (in && symb != dest.del) {
        in.setstate(std::ios::failbit);
    }
    return in;
}

std::istream& operator>>(std::istream& in, intIO&& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry) {
        return in;
    }
    in >> dest.ref;
    if (!in) {
        in.setstate(std::ios::failbit);
    }
    return in;
}

std::istream& operator>>(std::istream& in, Polygon& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry) {
        return in;
    }
    iofmtguard fmtguard(in);

    Polygon polygon;
    size_t size = 0;
    in >> size;
    if (size < 3 || in.fail())
    {
        in.setstate(std::ios::failbit);
        return in;
    }

    int temp = 0;
    for (size_t i = 0; i < size; ++i)
    {
        Point point;
        in >> DelimiterIO{ '(' } >> intIO{ temp };
        point.x = temp;
        in >> DelimiterIO{ ';' } >> intIO{ temp };
        point.y = temp;
        in >> DelimiterIO{ ')' };
        if (in) {
            polygon.points.push_back(point);
        }
    }
    if (polygon.points.size() == size) {
        dest = polygon;
    }
    else {
        in.setstate(std::ios::failbit);
    }
    return in;
}

iofmtguard::iofmtguard(std::basic_ios<char>& s) noexcept :
    s_(s),
    fill_(s.fill()),
    precision_(s.precision()),
    fmt_(s.flags()) {}

iofmtguard::~iofmtguard() {
    s_.fill(fill_);
    s_.precision(precision_);
    s_.flags(fmt_);
}
