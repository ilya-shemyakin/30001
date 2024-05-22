#include "commandOfFigure.h"
#include <algorithm>
#include <iomanip>
#include <numeric>
#include <iostream>
#include "iofmtguard.h"
void warning(std::ostream& output, const std::string& mes)
{
    output << mes;
}
double sumOfArea(double sum, const Polygon& polygon)
{
    sum += getArea(polygon);
    return sum;
}

double calculatePolygonAreaRec(const Polygon& polygon, size_t i, double area)
{
    const size_t numPoints = polygon.points_.size();
    if (i >= numPoints)
    {
        return area;
    }
    const Point& p1 = polygon.points_[i];
    const Point& p2 = polygon.points_[(i + 1) % numPoints];
    return calculatePolygonAreaRec(polygon, i + 1, area + (p1.x * p2.y - p2.x * p1.y));
}

double getArea(const Polygon& polygon)
{
    return 0.5 * std::abs(calculatePolygonAreaRec(polygon, 0, 0.0));
}
void evenAreaOfFigure(const std::vector< Polygon >& polygons, std::ostream& output)
{
    std::vector< Polygon > evenPolygons;
    std::copy_if
            (
                    polygons.begin(),
                    polygons.end(),
                    std::back_inserter(evenPolygons),
                    [](const Polygon& pol) { return pol.points_.size() % 2 == 0; }
            );
    double sumArea = std::accumulate(evenPolygons.begin(), evenPolygons.end(), 0.0, sumOfArea);
    output << std::fixed << std::setprecision(1) << sumArea << "\n";
}
void oddAreaOfFigure(const std::vector< Polygon >& polygons, std::ostream& output)
{
    std::vector< Polygon > evenPolygons;
    std::copy_if
            (
                    polygons.begin(),
                    polygons.end(),
                    std::back_inserter(evenPolygons),
                    [](const Polygon& pol) { return pol.points_.size() % 2 == 1; }
            );
    double sumArea = std::accumulate(evenPolygons.begin(), evenPolygons.end(), 0.0, sumOfArea);
    output << std::fixed << std::setprecision(1) << sumArea << "\n";
}

void meanAreaOfFigure(const std::vector< Polygon >& polygons, std::ostream& output)
{
    auto warningInvCom = std::bind(warning, std::placeholders::_1, "<INVALID COMMAND>\n");
    if(polygons.empty())
    {
        warningInvCom(output);
    }
    else
    {
        double sumArea = std::accumulate(polygons.begin(), polygons.end(), 0.0, sumOfArea) / polygons.size();
        output << std::fixed << std::setprecision(1) << sumArea << "\n";
    }
}
//cmdarea
void getAreaOfFigure(const std::vector< Polygon >& polygons, std::istream& input, std::ostream& output)
{
    using namespace std::placeholders;
    std::map< std::string, std::function< void(const std::vector< Polygon >&, std::ostream&) > > cmdsArea;
    cmdsArea["EVEN"] = std::bind(evenAreaOfFigure, _1, _2);
    cmdsArea["ODD"] = std::bind(oddAreaOfFigure, _1, _2);
    cmdsArea["MEAN"] = std::bind(meanAreaOfFigure, _1, _2);
    auto warningInvCom = std::bind(warning, _1, "<INVALID COMMAND>\n");
    std::string areaType;
    input >> areaType;
    try
    {
        cmdsArea.at(areaType)(polygons, output);
    }
    catch (const std::out_of_range& e)
    {
        if (std::isdigit(areaType[0]))
        {
            size_t num = std::stoull(areaType);
            if (num < 3)
            {
                warningInvCom(output);
            }
            else
            {
                vertexArea(num, polygons, output);
            }
        }
        else
        {
            warningInvCom(output);
        }
    }
}
void vertexArea(size_t num, const std::vector< Polygon >& polygons, std::ostream& output)
{
    std::vector< Polygon > needPolygons;
    std::copy_if
            (
                    polygons.begin(),
                    polygons.end(),
                    std::back_inserter(needPolygons),
                    [num](const Polygon& pol) { return pol.points_.size() == num; }
            );
    double sumArea = std::accumulate(needPolygons.begin(), needPolygons.end(), 0.0, sumOfArea);
    output << std::fixed << std::setprecision(1) << sumArea << "\n";
}
void maxArea(const std::vector< Polygon >& polygons, std::ostream& output)
{
    std::vector< double > areasOfPolygons;
    std::transform(polygons.begin(), polygons.end(), std::back_inserter(areasOfPolygons), getArea);
    std::sort(areasOfPolygons.begin(), areasOfPolygons.end());
    output << std::fixed << std::setprecision(1) << areasOfPolygons[areasOfPolygons.size() - 1] << "\n";
}
void cmdCount(const std::vector< Polygon >& polygons, std::istream& input, std::ostream& output)
{
    using namespace std::placeholders;
    std::map< std::string, std::function< void(const std::vector< Polygon >&, std::ostream&) > > cmdsCount;
    cmdsCount["EVEN"] = std::bind(countEven, _1, _2);
    cmdsCount["ODD"] = std::bind(countOdd, _1, _2);
    auto warningInvCom = std::bind(warning, _1, "<INVALID COMMAND>\n");
    std::string countType;
    input >> countType;
    try
    {
        cmdsCount.at(countType)(polygons, output);
    }
    catch (const std::out_of_range& e)
    {
        if (std::isdigit(countType[0]))
        {
            size_t num = std::stoull(countType);
            if (num < 3)
            {
                warningInvCom(output);
            }
            else
            {
                vertexCount(num, polygons, output);
            }
        }
        else
        {
            throw std::invalid_argument("<INVALID COMMAND>\n");
        }
    }
}

void maxVertexes(const std::vector< Polygon >& polygons, std::ostream& output)
{
    std::vector< size_t > vertexes;
    std::transform
            (
                    polygons.begin(),
                    polygons.end(),
                    std::back_inserter(vertexes),
                    [](const Polygon& pol) { return pol.points_.size(); }
            );
    std::sort(vertexes.begin(), vertexes.end());
    output << vertexes[vertexes.size() - 1] << "\n";
}

void minArea(const std::vector< Polygon >& polygons, std::ostream& output)
{
    std::vector< double > areasOfPolygons;
    std::transform(polygons.begin(), polygons.end(), std::back_inserter(areasOfPolygons), getArea);
    std::sort(areasOfPolygons.begin(), areasOfPolygons.end());
    output << std::fixed << std::setprecision(1) << areasOfPolygons[0];
}

void minVertexes(const std::vector< Polygon >& polygons, std::ostream& output)
{
    std::vector< size_t > vertexes;
    std::transform
            (
                    polygons.begin(),
                    polygons.end(),
                    std::back_inserter(vertexes),
                    [](const Polygon& pol) { return pol.points_.size(); }
            );
    std::sort(vertexes.begin(), vertexes.end());
    output << vertexes[0];
}

void max(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
    using namespace std::placeholders;
    std::map< std::string, std::function< void(const std::vector< Polygon >&, std::ostream&) > > cmdsMax;
    cmdsMax["AREA"] = std::bind(maxArea, _1, _2);
    cmdsMax["VERTEXES"] = std::bind(maxVertexes, _1, _2);
    auto warningInvCom = std::bind(warning, _1, "<INVALID COMMAND>\n");
    std::string maxType;
    in >> maxType;
    try
    {
        if(polygons.empty())
        {
            warningInvCom(out);
        }
        else
        {
            cmdsMax.at(maxType)(polygons, out);
        }
    }
    catch (const std::out_of_range& e)
    {
        warningInvCom(out);
    }
}

void min(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
    using namespace std::placeholders;
    std::map< std::string, std::function< void(const std::vector< Polygon >&, std::ostream&) > > cmdsMin;
    cmdsMin["AREA"] = std::bind(minArea, _1, _2);
    cmdsMin["VERTEXES"] = std::bind(minVertexes, _1, _2);
    auto warningInvCom = std::bind(warning, _1, "<INVALID COMMAND>\n");
    std::string minType;
    in >> minType;
    try
    {
        if(polygons.empty())
        {
            warningInvCom(out);
        }
        cmdsMin.at(minType)(polygons, out);
    }
    catch (const std::out_of_range& e)
    {
        warningInvCom(out);
    }
}

void area(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
    iofmtguard guard(out);
    std::string string;
    in >> string; //
    out << std::fixed << std::setprecision(1);
    getAreaOfFigure(polygons, std::cin, std::cout);
}

void countEven(const std::vector< Polygon >& polygons, std::ostream& output)
{
    size_t result = std::count_if
            (
                    polygons.begin(),
                    polygons.end(),
                    [](const Polygon& pol) { return pol.points_.size() % 2 == 0; }
            );
    output << result << "\n";
}

void countOdd(const std::vector< Polygon >& polygons, std::ostream& output)
{
    size_t result = std::count_if
            (
                    polygons.begin(),
                    polygons.end(),
                    [](const Polygon& pol) { return pol.points_.size() % 2 != 0; }
            );
    output << result << "\n";
}

void vertexCount(size_t num, const std::vector< Polygon >& polygons, std::ostream& output)
{
    size_t result = std::count_if
            (
                    polygons.begin(),
                    polygons.end(),
                    [num](const Polygon& pol) { return pol.points_.size() == num; }
            );
    output << result << "\n";
}

void count(const std::vector< Polygon >& polygons, std::istream& input, std::ostream& output)
{
    using namespace std::placeholders;
    std::map< std::string, std::function< void(const std::vector< Polygon >&, std::ostream&) > > cmdsCount;
    cmdsCount["EVEN"] = std::bind(countEven, _1, _2);
    cmdsCount["ODD"] = std::bind(countOdd, _1, _2);
    auto warningInvCom = std::bind(warning, _1, "<INVALID COMMAND>\n");
    std::string countType;
    input >> countType;
    try
    {
        cmdsCount.at(countType)(polygons, output);
    }
    catch (const std::out_of_range& e)
    {
        if (std::isdigit(countType[0]))
        {
            size_t num = std::stoull(countType);
            if (num < 3)
            {
                warningInvCom(output);
            }
            else
            {
                vertexCount(num, polygons, output);
            }
        }
        else
        {
            warningInvCom(output);
        }
    }
}
void intersections(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
    Polygon polygon;
    in >> polygon;

    if (polygons.empty() or (in.peek() != '\n' or !in))
    {
        throw std::invalid_argument("");
    }
    using namespace std::placeholders;
    auto intersectPredicate = std::bind(isIntersectionChecks, std::cref(polygon), _1);
    out << std::count_if(polygons.cbegin(), polygons.cend(), intersectPredicate);
}

void rmecho(std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
    using namespace std::placeholders;
    Polygon figure;
    in >> figure;
    if (polygons.empty()  or !in || in.peek() != '\n')
    {
        in.setstate(std::ios::failbit);
    }
    auto identical = std::bind(EqualFigures {figure}, _1, _2);
    auto last = std::unique(polygons.begin(), polygons.end(), identical);
    size_t removeFigure = std::distance(last, polygons.end());
    polygons.erase(last, polygons.end());
    out << removeFigure;
}
