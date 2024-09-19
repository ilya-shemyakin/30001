#include "Polygon.h"

std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry) {
        return in;
    }
    char symb = '0';
    in >> symb;
    if (in && symb != dest.exp) {
        in.setstate(std::ios::failbit);
    }
    return in;
}

std::istream& operator>>(std::istream& in, Point& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry) {
        return in;
    }
    return in >> DelimiterIO{ '(' } >> dest.x >> DelimiterIO{ ';' }
    >> dest.y >> DelimiterIO{ ')' };
}

std::istream& operator>>(std::istream& in, Polygon& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry) {
        return in;
    }
    dest.points.clear();
    size_t nPoint = 0;
    in >> nPoint;
    std::string str;
    std::getline(in, str, '\n');
    std::istringstream input(str);
    if (!input || nPoint < 3) {
        in.setstate(std::ios::failbit);
        return in;
    }
    else {
        std::vector < Point > temp{};
        std::copy(std::istream_iterator< Point >(input), std::istream_iterator< Point >(),
            std::back_inserter(temp));
        if (temp.size() == nPoint && temp.size() >= 3) {
            dest.points = temp;
        }
        else {
            in.setstate(std::ios::failbit);
        }
        return in;
    }
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
