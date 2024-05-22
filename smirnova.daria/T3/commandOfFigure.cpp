#include "commandOfFigure.h"
#include <algorithm>
#include <iomanip>
#include <numeric>
#include <iostream>
#include "iofmtguard.h"

double sumOfArea(double sum, const Polygon& polygon)
{
    sum += getArea(polygon);
    return sum;
}
double getPolygonAreas(const Point &p1, const Point &p2)
{
    return (p1.x * p2.y - p1.y * p2.x);
}

double getArea(const Polygon& polygon)
{
    double area = 0.0;
    size_t size = polygon.points_.size();
    for (size_t i = 0; i < size; ++i)
    {
        area += getPolygonAreas(polygon.points_[i], polygon.points_[(i + 1) % size]);
    }
    area = std::abs(area / 2.0);

    return area;
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
    if (polygons.empty())
    {
        throw std::invalid_argument("");
    }
    else
    {
        double sumArea = std::accumulate(polygons.begin(), polygons.end(), 0.0, sumOfArea) / polygons.size();
        output << std::fixed << std::setprecision(1) << sumArea << "\n";
    }
}

size_t numOfVertexes(const std::string& command, const std::vector< Polygon >& polygons)
{
    using namespace std::placeholders;
    using Command = std::function< bool(const Polygon&) >;
    std::map< std::string, Command > commands;
    {
        commands["EVEN"] = std::bind(isEven, _1);
        commands["ODD"] = std::bind(isOdd, _1);
    }
    Command counter;
    counter = commands.at(command);
    //Интерпретирует целое число без знака в строке str
    size_t number = std::stoull(command);
    if (number < 3)
    {
        throw std::invalid_argument("");
    }

    return std::count_if(polygons.cbegin(),polygons.cend(),std::bind(countFunctor, _1, number));
}

void getAreaOfFigure(const std::string& commands,  std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons)
{
    using namespace std::placeholders;
    std::map< std::string, std::function< void(const std::vector< Polygon >&, std::ostream&) >> command;
    command["EVEN"] = std::bind(evenAreaOfFigure, _1, _2);
    command["ODD"] = std::bind(oddAreaOfFigure, _1, _2);
    command["MEAN"] = std::bind(meanAreaOfFigure, _1, _2);
    std::string areaType;
    in >> areaType;
    try
    {
        command.at(areaType)(polygons, out);
    }
    catch (const std::out_of_range& e)
    {
        if (std::isdigit(areaType[0]))
        {
            size_t num = std::stoull(areaType);
            if (num < 3)
            {
                throw std::invalid_argument("");
            }
            else
            {
                numOfVertexes(commands, polygons);
            }
        }
        else
        {
            throw std::invalid_argument("");
        }
    }
}
    //if (commands == "EVEN")
    //{
    //    std::vector< Polygon > evenFigure;
    //    std::copy_if(std::begin(polygons), std::end(polygons), std::back_inserter(evenFigure), isEven);
    //
    //    PolygonsArea polygonsArea{ 0.0 };
    //    std::for_each(evenFigure.begin(), evenFigure.end(), std::ref(polygonsArea));
    //    out << std::fixed << out.precision(1);
    //    out << polygonsArea.area_ << "\n";
    //}
    //
    //if (commands == "ODD")
    //{
    //    std::vector< Polygon > oddFigure;
    //    std::copy_if(std::begin(polygons), std::end(polygons), std::back_inserter(oddFigure), isOdd);
    //
    //    PolygonsArea polygonsArea{ 0.0 };
    //    std::for_each(oddFigure.begin(), oddFigure.end(), std::ref(polygonsArea));
    //    out << std::fixed << out.precision(1);
    //    out << polygonsArea.area_ << "\n";
    //}
    //
    //if (commands == "MEAN")
    //{
    //
    //    PolygonsArea polygonsArea{ 0.0 };
    //    std::for_each(polygons.begin(), polygons.end(), std::ref(polygonsArea));
    //    out << std::fixed << out.precision(1);
    //    out << (polygonsArea.area_ / polygons.size()) << "\n"; //вычисление среднего знач
    //}
bool countFunctor(const Polygon& polygon, std::size_t size)
{
    return polygon.points_.size() == size;
}

bool isEvenOddCountFunctor(const Polygon& polygon)
{
    return polygon.points_.size() % 2;
}
void maxArea(const std::vector< Polygon >& polygons, std::ostream& output)
{
    std::vector< double > areasOfPolygons;
    std::transform(polygons.begin(), polygons.end(), std::back_inserter(areasOfPolygons), getArea);
    std::sort(areasOfPolygons.begin(), areasOfPolygons.end());
    output << std::fixed << std::setprecision(1) << areasOfPolygons[areasOfPolygons.size() - 1] << "\n";
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
    if (polygons.empty())
    {
        throw std::invalid_argument("");
    }
    using namespace std::placeholders;
    using Command = std::function< void() >;
    std::string string;
    in >> string;
    Command maxCommand;
    std::map< std::string, Command > commands;
    {
        commands["AREA"] = std::bind(maxArea, std::cref(polygons), std::ref(out));
        commands["VERTEXES"] = std::bind(maxVertexes, std::cref(polygons), std::ref(out));
    }

    maxCommand = commands.at(string);
    maxCommand();
}

void min(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
    if (polygons.empty())
    {
        throw std::invalid_argument("");
    }
    std::string string;
    in >> string;
    using namespace std::placeholders;
    using Command = std::function< void() >;
    Command minCommand;
    std::map< std::string, Command > commands;
    {
        commands["AREA"] = std::bind(minArea, std::cref(polygons), std::ref(out));
        commands["VERTEXES"] = std::bind(minVertexes, std::cref(polygons), std::ref(out));
    }

    minCommand = commands.at(string);
    minCommand();
}

void area(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
    iofmtguard guard(out);
    std::string string;
    in >> string; //
    out << std::fixed << std::setprecision(1);
    getAreaOfFigure(string, std::cin, std::cout, polygons);
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
                throw std::invalid_argument("");
            }
            else
            {
                vertexCount(num, polygons, output);
            }
        }
        else
        {
            throw std::invalid_argument("");
        }
    }
}
void intersections(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
    Polygon polygon;
    in >> polygon;
    if (polygons.empty() or (in.peek() != '\n' or !in))
    {
        throw std::logic_error("");
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
