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

    if (polygon.points.size()) {
        char b = ' ';
        iss >> b;
        std::cout << b; 
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