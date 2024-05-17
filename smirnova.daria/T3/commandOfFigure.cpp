#include "commandOfFigure.h"
#include <algorithm>
#include <iomanip>
#include <numeric>
#include <iostream>
#include "iofmtguard.h"

double PolygonArea::operator()(double areaOfFigure, const Point& p2, const Point& p3)
{
   areaOfFigure += std::abs((p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y));
   p1 = p2;
   return areaOfFigure;
}

void getAreaOfFigure(const std::string& commands, std::ostream& out, const std::vector< Polygon >& polygons)
{
    if (polygons.size() == 0)
    {
        throw std::logic_error(ERROR_IN_COMMAND);
    }

    if (commands == "EVEN")
    {
        std::vector< Polygon > evenFigure;
        std::copy_if(std::begin(polygons), std::end(polygons), std::back_inserter(evenFigure), isEven);

        PolygonsArea polygonsArea{ 0.0 };
        std::for_each(evenFigure.begin(), evenFigure.end(), std::ref(polygonsArea));
        out << std::fixed << out.precision(1);
        out << polygonsArea.area_ << "\n";
    }

    if (commands == "ODD")
    {
        std::vector< Polygon > oddFigure;
        std::copy_if(std::begin(polygons), std::end(polygons), std::back_inserter(oddFigure), isOdd);

        PolygonsArea polygonsArea{ 0.0 };
        std::for_each(oddFigure.begin(), oddFigure.end(), std::ref(polygonsArea));
        out << std::fixed << out.precision(1);
        out << polygonsArea.area_ << "\n";
    }

    if (commands == "MEAN")
    {

        PolygonsArea polygonsArea{ 0.0 };
        std::for_each(polygons.begin(), polygons.end(), std::ref(polygonsArea));
        out << std::fixed << out.precision(1);
        out << (polygonsArea.area_ / polygons.size()) << "\n"; //вычисление среднего знач
    }
}
bool countFunctor(const Polygon& polygon, std::size_t size)
{
    return polygon.points_.size() == size;
}
size_t numOfVertexes(const std::string& command, const std::vector< Polygon >& polygons)
{
    using namespace std::placeholders;
    using Command = std::function< bool(const Polygon&) >;
    std::map< std::string, Command > commands;
    {
        commands["EVEN"] = std::bind(isEvenOddCountFunctor, _1);
        commands["ODD"] = std::bind(isEvenOddCountFunctor, _1);
    }
    Command counter;
    counter = commands.at(command);
    //Интерпретирует целое число без знака в строке str
    size_t number = std::stoull(command);
    if (number < 3)
    {
        throw std::logic_error(ERROR_IN_COMMAND);
    }

    return std::count_if(polygons.cbegin(),polygons.cend(),std::bind(countFunctor, _1, number));
}

bool isEvenOddCountFunctor(const Polygon& polygon)
{
    return polygon.points_.size() % 2;
}
void getMinArea(const std::vector< Polygon >& polygons, std::ostream& out)
{
    iofmtguard guard(out);
    out << std::fixed << std::setprecision(1);
    out << std::min_element(polygons.cbegin(), polygons.cend(), compareAreas)->getArea();
}

void getMaxArea(const std::vector< Polygon >& polygons, std::ostream& out)
{
    iofmtguard guard(out);
    out << std::fixed << std::setprecision(1);
    out << std::max_element(polygons.cbegin(), polygons.cend(), compareAreas)->getArea();
}

void getMinVertex(const std::vector< Polygon >& polygons, std::ostream& out)
{
    iofmtguard guard(out);
    out << std::fixed << std::setprecision(1);
    out << std::min_element(polygons.cbegin(), polygons.cend(), compareVertexesArea)->points_.size();
}

void getMaxVertex(const std::vector< Polygon >& polygons, std::ostream& out)
{
    iofmtguard guard(out);
    out << std::fixed << std::setprecision(1);
    out << std::max_element(polygons.cbegin(), polygons.cend(), compareVertexesArea)->points_.size();
}

void area(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
    iofmtguard guard(out);
    std::string string;
    in >> string;
    out << std::fixed << std::setprecision(1);
    getAreaOfFigure(string, std::cout, polygons);
}
void max(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
    if (polygons.empty())
    {
        throw std::invalid_argument(ERROR_IN_COMMAND);
    }
    using namespace std::placeholders;
    using Command = std::function< void() >;
    std::string string;
    in >> string;
    Command maxCommand;
    std::map< std::string, Command > commands;
    {
        commands["AREA"] = std::bind(getMaxArea, std::cref(polygons), std::ref(out));
        commands["VERTEXES"] = std::bind(getMaxVertex, std::cref(polygons), std::ref(out));
    }

    maxCommand = commands.at(string);
    maxCommand();
}

void min(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
    if (polygons.empty())
    {
        throw std::invalid_argument(ERROR_IN_COMMAND);
    }
    std::string string;
    in >> string;
    using namespace std::placeholders;
    using Command = std::function< void() >;
    Command minCommand;
    std::map< std::string, Command > commands;
    {
        commands["AREA"] = std::bind(getMinArea, std::cref(polygons), std::ref(out));
        commands["VERTEXES"] = std::bind(getMinVertex, std::cref(polygons), std::ref(out));
    }

    minCommand = commands.at(string);
    minCommand();
}
void count(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
    iofmtguard guard(out);
    std::string string;
    in >> string;
    out << numOfVertexes(string, polygons);
}

void intersections(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
    Polygon polygon;
    in >> polygon;
    if (polygons.empty() or (in.peek() != '\n' or !in))
    {
        throw std::logic_error(ERROR_IN_COMMAND);
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
        throw std::invalid_argument(ERROR_IN_COMMAND);
    }
    auto identical = std::bind(EqualFigures {figure}, _1, _2);
    auto last = std::unique(polygons.begin(), polygons.end(), identical);
    size_t removeFigure = std::distance(last, polygons.end());
    polygons.erase(last, polygons.end());
    out << removeFigure;
}
