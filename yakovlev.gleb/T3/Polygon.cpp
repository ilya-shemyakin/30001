#include "Polygon.h"

std::istream& operator>>(std::istream& in, DelimiterIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) {
        return in;
    }
    char c = '\0';
    in >> c;

    if (in && (std::toupper(c) != std::toupper(dest.exp))) {
        in.setstate(std::ios::failbit);
    }
    return in;
}

std::istream& operator>>(std::istream& in, IntIO&& dest) {
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

std::istream& operator>>(std::istream& in, Polygon& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) {
        return in;
    }

    Polygon polygon;
    long unsigned int corners = 0;

    in >> corners;

    if (corners < 3) {
        in.setstate(std::ios::failbit);
        return in;
    }

    for (long unsigned int i = 0; i < corners; ++i) {
        Point point;
        in >> DelimiterIO{ '(' } >> IntIO{ point.x };
        in >> DelimiterIO{ ';' } >> IntIO{ point.y };
        in >> DelimiterIO{ ')' };
        if (in) {
            polygon.points.push_back(point);
        }
    }

    if (polygon.points.size() == corners) {
        dest = polygon;
    }
    else{
        in.setstate(std::ios::failbit);
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const Point& dest) {
    std::ostream::sentry sentry(out);
    if (!sentry) {
        return out;
    }
    return (out << '(' << dest.x << ';' << dest.y << ')');
}

std::ostream& operator<<(std::ostream& out, const Polygon& dest) {
    std::ostream::sentry sentry(out);
    if (!sentry) {
        return out;
    }

    int s = dest.points.size();
    out << s;
    std::copy(
        std::begin(dest.points),
        std::end(dest.points),
        std::ostream_iterator< Point >(std::cout << ' ')
    );

    return out;
}
