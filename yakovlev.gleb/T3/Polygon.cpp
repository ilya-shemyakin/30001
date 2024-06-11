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

    int temp = 0;
    for (long unsigned int i = 0; i < corners; ++i) {
        Point point;
        in >> DelimiterIO{ '(' } >> IntIO{ temp };
        point.x = temp;
        in >> DelimiterIO{ ';' } >> IntIO{ temp };
        point.y = temp;
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
