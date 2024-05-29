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
    int corners = 0;
    in >> corners;

    if (corners < 3) {
        in.setstate(std::ios::failbit);
        return in;
    }

    std::string pol = "";
    std::getline(in, pol, '\n');
    std::istringstream iss(pol);

    int temp = 0;
    for (int i = 0; i < corners; ++i) {
        Point point;
        iss >> DelimiterIO{ '(' } >> IntIO{ temp };
        point.x = temp;
        iss >> DelimiterIO{ ';' } >> IntIO{ temp };
        point.y = temp;
        iss >> DelimiterIO{ ')' };
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
