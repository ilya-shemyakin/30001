#include "Polygon.h"

std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    char symb = '0';
    in >> symb;
    if (in && (std::tolower(symb) != std::tolower(dest.exp)))
    {
        in.setstate(std::ios::failbit);
    }
    return in;
}


std::istream& operator>>(std::istream& in, intIO&& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }

    in >> dest.ref;
    if (!in)
    {
        in.setstate(std::ios::failbit);
    }
    return in;
}

std::istream& operator>>(std::istream& in, Point& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }

    return in >> DelimiterIO{ '(' } >> dest.x >> DelimiterIO{ ';' }
    >> dest.y >> DelimiterIO{ ')' };
}

//формат ввода      3 (1;1) (1;3) (3;3)
std::istream& operator>>(std::istream& in, Polygon& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
//Iofmtguard fmtguard(in);

//Polygon polygon;

    int nPoints = 0;
    in >> nPoints;
    std::string localString;
    std::getline(in, localString, '\n');
    std::istringstream inString(localString);
    if (!inString || nPoints < 3)
    {
        in.setstate(std::ios::failbit);
        return in;
    }

    std::vector < Point > locPoints{};

    std::copy(std::istream_iterator< Point >(inString), std::istream_iterator< Point >(),
        std::back_inserter(locPoints));
    if (locPoints.size() == nPoints && nPoints >= 3)
    {
        dest.points = locPoints;
    }
    else
    {
        in.setstate(std::ios::failbit);
    }
    return in;
}
