#include "polygonCommands.h"

using namespace std::placeholders;

//shoelace formula, also known as Gauss's area formula
int getShoelaceMultiplication(const Point& p1, const Point& p2)
{
    /*std::cout << "p1 (" << p1.x << ";" << p1.y
        << ") p2 (" << p2.x << ";" << p2.y << ")\n";*/
    return (p1.x * p2.y - p1.y * p2.x);
}

double getArea(const Polygon& polygon)
{
    double area = 0.0;
    size_t size = polygon.points.size();
    for (size_t i = 0; i < size; i++) {
        area += getShoelaceMultiplication(polygon.points[i], polygon.points[(i + 1)%size]);
    }
    return std::abs(area) / 2.0;
}

void area(std::vector< Polygon >& polygons, std::string& mode, std::ostream& out)
{
    out << std::fixed << std::setprecision(1);
    if (mode == "EVEN") {
        out << std::accumulate(polygons.begin(), polygons.end(), 0.0,
            [](double area, const Polygon& polygon)
            {
                area += (polygon.points.size() % 2 == 0) ? getArea(polygon) : 0.0;
                return area;
            }) << std::endl;
    }
    else if (mode == "ODD") {
        out << std::accumulate(polygons.begin(), polygons.end(), 0.0,
            [](double area, const Polygon& polygon)
            {
                area += (polygon.points.size() % 2 != 0) ? getArea(polygon) : 0.0;
                return area;
            }) << std::endl;
    }
    else if (mode == "MEAN") {
        if (polygons.empty()) {
            throw std::invalid_argument("");
        }
        out << (std::accumulate(polygons.begin(), polygons.end(), 0.0,
            [](double area, const Polygon& polygon)
            {
                area += getArea(polygon);
                return area;
            })) / polygons.size() << std::endl;
    }
    else {
        size_t size = std::stoul(mode);
        if (size <= 2) {
            throw std::invalid_argument("");
        }
        out << std::accumulate(polygons.begin(), polygons.end(), 0.0,
            [size](double area, const Polygon& polygon)
            {
                area += (polygon.points.size() == size) ? getArea(polygon) : 0.0;
                return area;
            }) << std::endl;
    }
}

void max(std::vector< Polygon >& polygons, std::string& mode, std::ostream& out)
{
    if (!polygons.empty() && mode == "AREA") {
        std::vector<Polygon>::iterator maxArea;
        maxArea = std::max_element(polygons.begin(), polygons.end(),
            std::bind(std::less<double>{}, std::bind(getArea, _1), std::bind(getArea, _2)));

        out << std::fixed << std::setprecision(1)
            << getArea(*maxArea) << std::endl;
    }
    else if (!polygons.empty() && mode == "VERTEXES") {
        std::vector<Polygon>::iterator maxVertexes;
        maxVertexes = std::max_element(polygons.begin(), polygons.end(),
            std::bind(std::less<double>{},
                std::bind(&std::vector< Point >::size, std::bind(&Polygon::points, _1)),
                std::bind(&std::vector< Point >::size, std::bind(&Polygon::points, _2))));

       out << (*maxVertexes).points.size() << std::endl;
    }
    else {
        throw std::invalid_argument("");
    }
}

void min(std::vector< Polygon >& polygons, std::string& mode, std::ostream& out)
{
    if (!polygons.empty() && mode == "AREA") {
        std::vector<Polygon>::iterator minArea;
        minArea = std::min_element(polygons.begin(), polygons.end(),
            std::bind(std::less<double>{},
                std::bind(getArea, _1),
                std::bind(getArea, _2)));

        out << std::fixed << std::setprecision(1)
            << getArea(*minArea) << std::endl;
    }
    else if (!polygons.empty() && mode == "VERTEXES") {
        std::vector<Polygon>::iterator minVertexes;
        minVertexes = std::min_element(polygons.begin(), polygons.end(),
            std::bind(std::less<double>{},
                std::bind(&std::vector< Point >::size, std::bind(&Polygon::points, _1)),
                std::bind(&std::vector< Point >::size, std::bind(&Polygon::points, _2))));

        out << (*minVertexes).points.size() << std::endl;
    }
    else {
        throw std::invalid_argument("");
    }
}

void count(std::vector< Polygon >& polygons, std::string& mode, std::ostream& out)
{
    if (mode == "EVEN") {
        out << std::count_if(polygons.begin(), polygons.end(),
            [](const Polygon& polygon) {
                return polygon.points.size() % 2 == 0;
            }) << std::endl;
    }
    else if (mode == "ODD") {
        out << std::count_if(polygons.begin(), polygons.end(),
            [](const Polygon& polygon) {
                return polygon.points.size() % 2 != 0;
            }) << std::endl;
    }
    else {
        size_t size = std::stoul(mode);
        if (size <= 2) {
            throw std::invalid_argument("");
        }
        out << std::count_if(polygons.begin(), polygons.end(),
            [size](const Polygon& polygon)
            {
                return polygon.points.size() == size;
            }) << "\n";
    }
}

void lessarea(std::vector< Polygon >& polygons, Polygon& dest, std::ostream& out)
{
    out << std::count_if(polygons.begin(), polygons.end(),
        [&dest](const Polygon& polygon)
        {
            return getArea(dest) > getArea(polygon);
        }) << std::endl;
}

//как по другому реализовать
void maxseq(std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
    Polygon dest;
    in >> dest;
    if (in.fail() || polygons.size() == 0) {
        throw std::invalid_argument("");
    }
    else {
        int currentCount = 0;
        auto seqs = std::accumulate(polygons.begin(), polygons.end(), std::vector < size_t >(),
            [&dest, &currentCount](std::vector< size_t >& seqs, const Polygon& polygon)
            {
                if (polygon == dest && currentCount==0) {
                    currentCount++;
                    seqs.push_back(1);
                }
                else if (polygon == dest) {
                    *(--seqs.end()) += 1;
                }
                else {
                    currentCount = 0;
                }
                return seqs;
            });
        seqs.push_back(0);
        out << *std::max_element(seqs.begin(), seqs.end()) << std::endl;
    }
}
