#include "commandOfFigure.h"
#include <algorithm>
#include <iomanip>
#include <numeric>
#include <iostream>
#include "iofmtguard.h"
void areaOfFigure(const std::vector< Polygon >& polygons, std::istream& input, std::ostream& output)
{
    using namespace std::placeholders;
    std::map< std::string, std::function< void(const std::vector< Polygon >&, std::ostream&) > > cmdsArea;
    cmdsArea["EVEN"] = std::bind(evenArea, _1, _2); //четные
    cmdsArea["ODD"] = std::bind(oddArea, _1, _2); //нечет
    cmdsArea["MEAN"] = std::bind(meanArea, _1, _2);
    std::string areaType; //even/odd/mean
    input >> areaType;
    try
    {
        cmdsArea.at(areaType)(polygons, output); //вызываем ту или иную функцию из трех
    }
    catch (const std::out_of_range& e)
    {
        if (std::isdigit(areaType[0])) //проверка, является ли строковый элемент цифрой или нет
        {
            size_t number = std::stoull(areaType); //Интерпретирует целое число без знака в строке str
            if (number < 3)
            {
                throw std::invalid_argument("");
            }
            else
            {
                vertexArea(number, polygons, output);
            }
        }
        else
        {
            throw std::invalid_argument("");
        }
    }
}

void evenArea(const std::vector< Polygon >& polygons, std::ostream& output)
{
    std::vector< Polygon > evenPolygons;
    std::copy_if
            (
                    polygons.begin(),
                    polygons.end(),
                    std::back_inserter(evenPolygons),
                    [](const Polygon& polygon) { return polygon.points_.size() % 2 == 0; }
            );
    double sumArea = std::accumulate(evenPolygons.begin(), evenPolygons.end(), 0.0, plusArea);
    //суммирует всю последовательность
    output << std::fixed << std::setprecision(1) << sumArea << "\n"; //один знак после запятой
}

void oddArea(const std::vector< Polygon >& polygons, std::ostream& output)
{
    std::vector< Polygon > oddPolygons;
    std::copy_if
            (
                    polygons.begin(),
                    polygons.end(),
                    std::back_inserter(oddPolygons),
                    [](const Polygon& pol) { return pol.points_.size() % 2 != 0; }
            );
    double sumArea = std::accumulate(oddPolygons.begin(), oddPolygons.end(), 0.0, plusArea);
    output << std::fixed << std::setprecision(1) << sumArea << "\n";
}

void meanArea(const std::vector< Polygon >& polygons, std::ostream& output)
{
    if (polygons.empty()) //в усл написано что надо сделать проверку у mean
    {
        throw std::invalid_argument("");
    }
    else
    {
        double sumArea = std::accumulate(polygons.begin(), polygons.end(), 0.0, plusArea) / polygons.size();
        output << std::fixed << std::setprecision(1) << sumArea << "\n";
    }
}

void vertexArea(size_t vertex, const std::vector< Polygon >& polygons, std::ostream& output)
{
    std::vector< Polygon > needPolygons;
    std::copy_if
            (
                    polygons.begin(),
                    polygons.end(),
                    std::back_inserter(needPolygons),
                    [vertex](const Polygon& pol) { return pol.points_.size() == vertex; }
            );
    //автоматически вставляет новые элементы в конец
    double sumArea = std::accumulate(needPolygons.begin(), needPolygons.end(), 0.0, plusArea);
    output << std::fixed << std::setprecision(1) << sumArea << "\n";
}

double plusArea(double sum, const Polygon& polygon)
{
    sum += calculatePolygonArea(polygon);
    return sum;
}
double gaussFormula(const Point& p1, const Point& p2) {
    return (p1.x * p2.y - p2.x * p1.y);
}
double calculatePolygonAreaRec(const Polygon& polygon, size_t i, double area)
{
    const size_t numpoints_ = polygon.points_.size();
    if (i >= numpoints_)
    {
        return area;
    }
    const Point& p1 = polygon.points_[i];
    const Point& p2 = polygon.points_[(i + 1) % numpoints_];
    return calculatePolygonAreaRec(polygon, i + 1, area + gaussFormula(p1,p2));
}

double calculatePolygonArea(const Polygon& polygon)
{
    return 0.5 * std::abs(calculatePolygonAreaRec(polygon, 0, 0.0));
}

void maxOfFigure(const std::vector< Polygon >& polygons, std::istream& input, std::ostream& output)
{
    using namespace std::placeholders;
    std::map< std::string, std::function< void(const std::vector< Polygon >&, std::ostream&) > > cmdsMax;
    cmdsMax["AREA"] = std::bind(findMaxArea, _1, _2);
    cmdsMax["VERTEXES"] = std::bind(findMaxVertexes, _1, _2);
    std::string maxType;
    input >> maxType;
    try
    {
        if (polygons.empty())
        {
            throw std::invalid_argument("");
        }
        else
        {
            cmdsMax.at(maxType)(polygons, output);
        }
    }
    catch (const std::out_of_range& e)
    {
        throw std::invalid_argument("");
    }
}

void findMaxArea(const std::vector< Polygon >& polygons, std::ostream& output)
{
    output << std::fixed << std::setprecision(1);
    auto maxim = std::max_element(polygons.begin(), polygons.end(), compareArea);
    output << plusArea(0,*maxim) << '\n';
}

void findMaxVertexes(const std::vector< Polygon >& polygons, std::ostream& output)
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

void minOfFigure(const std::vector< Polygon >& polygons, std::istream& input, std::ostream& output)
{
    using namespace std::placeholders;
    std::map< std::string, std::function< void(const std::vector< Polygon >&, std::ostream&) > > cmdsMin;
    cmdsMin["AREA"] = std::bind(findMinArea, _1, _2);
    cmdsMin["VERTEXES"] = std::bind(findMinVertexes, _1, _2);
    std::string minType;
    input >> minType;
    try
    {
        if(polygons.empty())
        {
            throw std::invalid_argument("");
        }
        cmdsMin.at(minType)(polygons, output);
    }
    catch (const std::out_of_range& e)
    {
        throw std::invalid_argument("");
    }
}

void findMinArea(const std::vector< Polygon >& polygons, std::ostream& output)
{
    std::vector< double > areasOfPolygons;
    std::transform(polygons.begin(), polygons.end(), std::back_inserter(areasOfPolygons), calculatePolygonArea);
    std::sort(areasOfPolygons.begin(), areasOfPolygons.end());
    output << std::fixed << std::setprecision(1) << areasOfPolygons[0];
}

void findMinVertexes(const std::vector< Polygon >& polygons, std::ostream& output)
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

void countOfFigure(const std::vector< Polygon >& polygons, std::istream& input, std::ostream& output)
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
            throw std::invalid_argument("<INVALID COMMAND>\n");
        }
    }
}

void countEven(const std::vector< Polygon >& polygons, std::ostream& output)
{
using namespace std::placeholders;
    auto count = std::bind(std::equal_to<size_t>(),std::bind( //equal to сравнивает результат остатка от дел с 0
            std::modulus<size_t>(), //делит это количество точек на 2 и смотрит чет или нечет
            std::bind(
                    &std::vector<Point>::size, //узнает сколько точек есть в каждом полигоне
                    std::bind(&Polygon::points_, _1) //достает вектор точек для каждого полигона
            ),2), 0); //возвращает либо 1 если чет колво вершин или 0 если нечет
    size_t result = std::count_if
            (
                    polygons.begin(),
                    polygons.end(),
                    count
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

void intersections(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
    using namespace std::placeholders;
    Polygon polygon;
    in >> polygon;
    if (polygons.empty() or !in)
    {
        throw std::invalid_argument("");
    }
    auto intersect = std::bind(isIntersectionChecks, std::cref(polygon), _1);
    out << std::count_if(polygons.cbegin(), polygons.cend(), intersect);
}
void rmecho(std::vector<Polygon>& polygons, std::istream& in, std::ostream& out)
{
using namespace std::placeholders;
    Polygon polygon;
    input >> polygon;
    if (polygons.empty()  || !input)
    {
        input.setstate(std::ios::failbit);
    }
    auto identical = std::bind(equalPolygons, polygon, _2); //равна ди фигура вводному figure
    auto last = std::unique(polygons.begin(), polygons.end(), identical); //проверяем все фигуры на этот признак Удаляет все элементы, кроме первого, из каждой последовательной группы эквивалентных элементов
    size_t countDelPolygons = std::distance(last, polygons.end());
// Возвращает количество переходов от  first к  last
    polygons.erase(last, polygons.end());
    output << countDelPolygons << "\n";
}
