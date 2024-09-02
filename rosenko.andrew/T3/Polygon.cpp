#include "Polygon.h"

bool Point::operator ==(const Point& other) const
{
    return ((other.x == this->x) && (other.y == this->y));
}

bool Polygon::operator==(const Polygon& other) const
{
    if (vertexes.size() != other.vertexes.size())
    {
        return false;
    }
    return std::equal(other.vertexes.begin(), other.vertexes.end(),
        vertexes.begin(), vertexes.end());
}

std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    char symb = '0';
    in >> symb;
    if (in && symb != dest.exp)
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

std::istream& operator>>(std::istream& in, Polygon& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }

    dest.vertexes.clear();

    size_t nPoints = 0;
    in >> nPoints;
    std::string str;
    std::getline(in, str, '\n');
    std::istringstream input(str);
    if (!input || nPoints < 3)
    {
        in.setstate(std::ios::failbit);
        return in;
    }

    Polygon polygon;
    using input_it = std::istream_iterator< Point >;
    std::vector< Point > points;

    std::copy_n(input_it{ input }, nPoints, std::back_inserter(points));
    if (input)
    {
        polygon.vertexes = std::move(points);
    }
    if (input && nPoints == polygon.vertexes.size())
    {
        dest = polygon;
    }
    else
    {
        input.setstate(std::ios::failbit);
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const Point& point)
{
    out << "(" << point.x << "; " << point.y << ")";
    return out;
}

std::ostream& operator<<(std::ostream& out, const Polygon& polygon)
{
    out << "Polygon with vertexes: ";
    for (const auto& point : polygon.vertexes)
    {
        out << point << " ";
    }
    return out;
}
