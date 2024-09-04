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
    int temp = 0;

    in >> DelimiterIO{ '(' } >> intIO{ temp };
    dest.x = temp;
    in >> DelimiterIO{ ';' } >> intIO{ temp };
    dest.y = temp;
    in >> DelimiterIO{ ')' };
    return in;
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

    std::vector < Point > temp{};
    std::copy(std::istream_iterator< Point >(input), std::istream_iterator< Point >(),
        std::back_inserter(temp));

    if (temp.size() == nPoints && temp.size() >= 3)
    {
        dest.vertexes = temp;
    }
    else
    {
        in.setstate(std::ios::failbit);
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
    out << "Polygon with nPoints: ";
    for (const auto& point : polygon.vertexes)
    {
        out << point << " ";
    }
    return out;
}
