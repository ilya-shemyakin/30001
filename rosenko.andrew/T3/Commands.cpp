#include "Commands.h"

using namespace std::placeholders;

bool isEven(const Polygon& polygon)
{
    return !isOdd(polygon);
}

bool isOdd(const Polygon& polygon)
{
    return polygon.vertexes.size() % 2 != 0;
}

bool isDigit(char ch)
{
    return std::isdigit(ch);
}

double calcArea(const Polygon& polygon)
{
    const auto& vertexes = polygon.vertexes;

    double area = 0.0;
    size_t nVertices = vertexes.size();

    for (size_t i = 0; i < nVertices - 1; ++i)
    {
        area += (vertexes[i].x * vertexes[i + 1].y);
        area -= (vertexes[i].y * vertexes[i + 1].x);
    }
    area += (vertexes[nVertices - 1].x * vertexes[0].y);
    area -= (vertexes[0].x * vertexes[nVertices - 1].y);
    area /= 2;
    return std::fabs(area);
}

void area(std::vector< Polygon >& polygons, std::istream& input, std::ostream& output)
{
    output << std::fixed << std::setprecision(1);
    Iofmtguard fmtguard(output);
    std::string cmd;
    input >> cmd;

    if (cmd == "EVEN")
    {
        output << std::accumulate(polygons.begin(), polygons.end(), 0.0,
            [](double area, const Polygon& polygon)
            {
                area += (isEven(polygon)) ? calcArea(polygon) : 0.0;
                return area;
            }) << std::endl;
    }
    else if (cmd == "ODD")
    {
        output << std::accumulate(polygons.begin(), polygons.end(), 0.0,
            [](double area, const Polygon& polygon)
            {
                area += ((isOdd(polygon))) ? calcArea(polygon) : 0.0;
                return area;
            }) << std::endl;
    }
    else if (cmd == "MEAN")
    {
        if (polygons.empty())
        {
            throw std::invalid_argument("");
        }
        output << (std::accumulate(polygons.begin(), polygons.end(), 0.0,
            [](double area, const Polygon& polygon)
            {
                area += calcArea(polygon);
                return area;
            })) / polygons.size() << std::endl;
    }
    else if (std::all_of(cmd.begin(), cmd.end(), isDigit) == true)
    {
        size_t nVertices = std::stoull(cmd);
        if (nVertices <= 2)
        {
            throw std::invalid_argument("");
        }
        output << std::accumulate(polygons.begin(), polygons.end(), 0.0,
            [nVertices](double area, const Polygon& polygon)
            {
                area += (polygon.vertexes.size() == nVertices) ? calcArea(polygon) : 0.0;
                return area;
            }) << std::endl;
    }
    else
    {
        throw std::invalid_argument("");
    }
}

void max(std::vector< Polygon >& polygons, std::istream& input, std::ostream& output)
{
    Iofmtguard iofmtguard(std::cout);

    std::string cmd;
    input >> cmd;

    if (cmd == "AREA")
    {
        if (polygons.empty()) 
        {
            throw std::invalid_argument("");
            return;
        }
        output << std::fixed << std::setprecision(1);
        std::vector< double > areas;
        std::transform(polygons.begin(), polygons.end(), std::back_inserter(areas), calcArea);
        output << *std::max_element(areas.begin(), areas.end()) << '\n';

    }
    else if (cmd == "VERTEXES")
    {
        if (polygons.empty())
        {
            throw std::invalid_argument("");
            return;
        }
        std::vector< double > vertexes;
        std::transform(polygons.begin(), polygons.end(), std::back_inserter(vertexes),
            [](Polygon& polygon) { return polygon.vertexes.size(); });
        output << *std::max_element(vertexes.begin(), vertexes.end()) << '\n';
    }
    else
    {
        throw std::invalid_argument("");
        return;
    }
}

void min(std::vector< Polygon >& polygons, std::istream& input, std::ostream& output)
{
    std::string cmd;
    input >> cmd;

    if (cmd == "AREA")
    {
        if (polygons.empty())
        {
            throw std::invalid_argument("");
            return;
        }
        output << std::fixed << std::setprecision(1);
        std::vector< double > areas;
        std::transform(polygons.begin(), polygons.end(), std::back_inserter(areas), calcArea);
        output << *std::min_element(areas.begin(), areas.end()) << '\n';
    }
    else if (cmd == "VERTEXES")
    {
        if (polygons.empty())
        {
            throw std::invalid_argument("");
            return;
        }
        std::vector< double > vertexes;
        std::transform(polygons.begin(), polygons.end(), std::back_inserter(vertexes),
            [](Polygon& polygon) { return polygon.vertexes.size(); });
        output << *std::min_element(vertexes.begin(), vertexes.end()) << '\n';
    }
    else
    {
        throw std::invalid_argument("");
        return;
    }
}



void count(std::vector< Polygon >& polygons, std::istream& input, std::ostream& output)
{
    std::string cmd;
    input >> cmd;

    Iofmtguard fmtguard(output);
    if (cmd == "EVEN")
    {
        size_t nEven = std::count_if
        (
            polygons.begin(),
            polygons.end(),
            isEven
        );
        output << nEven << "\n";
    }
    else if (cmd == "ODD")
    {
        size_t nOdd = std::count_if
        (
            polygons.begin(),
            polygons.end(),
            isOdd
        );
        output << nOdd << "\n";
    }
    else if (std::all_of(cmd.begin(), cmd.end(), isDigit) == true)
    {
        size_t nVertices = std::stoull(cmd);

        size_t nParticular = std::count_if
        (
            polygons.begin(),
            polygons.end(),
            [nVertices](const Polygon& polygon) { return polygon.vertexes.size() == nVertices; }
        );
        output << nParticular << "\n";
    }
    else
    {
        throw std::invalid_argument("");
    }
}

void rmecho(std::vector< Polygon >& polygons, std::istream& input, std::ostream& output)
{
    size_t currentSize = polygons.size();
    if (currentSize == 0)
    {
        output << currentSize << "\n";
        return;
    }

    Polygon toErase;
    input >> toErase;

    bool islastRemoved = false;
    auto it = std::remove_if(polygons.begin(), polygons.end(),
        [&toErase, &islastRemoved](const Polygon& polygon)
        {
            if (polygon == toErase && islastRemoved)
            {
                return true;
            }
            islastRemoved = (polygon == toErase);
            return false;
        }
    );
    polygons.erase(it, polygons.end());
    size_t count = currentSize - polygons.size();
    output << count << '\n';
}

int getMaxCoordinate(const Polygon& polygon, int(*getCoordinate)(const Point& point))
{
    std::vector< int > coordinates;
    std::transform(polygon.vertexes.begin(), polygon.vertexes.end(),
        std::back_inserter(coordinates), getCoordinate);
    int maxCoordinate = *std::max_element(coordinates.begin(), coordinates.end());
    return maxCoordinate;
}

int getMinCoordinate(const Polygon& polygon, int(*getCoordinate)(const Point& point))
{
    std::vector< int > coordinates;
    std::transform(polygon.vertexes.begin(), polygon.vertexes.end(),
        std::back_inserter(coordinates), getCoordinate);
    int minCoordinate = *std::min_element(coordinates.begin(), coordinates.end());
    return minCoordinate;
}

int getX(const Point& point)
{
    return point.x;
}

int getY(const Point& point)
{
    return point.y;
}

std::vector< Point > getFrame(const std::vector< Polygon >& polygons)
{
    std::vector< int > allMaxX;
    std::vector< int > allMaxY;
    std::vector< int > allMinX;
    std::vector< int > allMinY;

    using namespace std::placeholders;
    std::transform(polygons.begin(), polygons.end(), std::back_inserter(allMaxX),
                    std::bind(getMaxCoordinate, _1, getX));
    std::transform(polygons.begin(), polygons.end(), std::back_inserter(allMaxY),
                    std::bind(getMaxCoordinate, _1, getY));
    std::transform(polygons.begin(), polygons.end(), std::back_inserter(allMinX),
                    std::bind(getMinCoordinate, _1, getX));
    std::transform(polygons.begin(), polygons.end(), std::back_inserter(allMinY),
                    std::bind(getMinCoordinate, _1, getY));

    int maxX = *std::max_element(allMaxX.begin(), allMaxX.end());
    int maxY = *std::max_element(allMaxY.begin(), allMaxY.end());
    int minX = *std::min_element(allMinX.begin(), allMinX.end());
    int minY = *std::min_element(allMinY.begin(), allMinY.end());
    std::vector < Point > frame;

    frame.push_back(Point{ minX, minY });
    frame.push_back(Point{ minX, maxY });
    frame.push_back(Point{ maxX, maxY });
    frame.push_back(Point{ maxX, minY });
    return frame;
}

bool isInFrame(std::vector< Point >& frame, const Polygon& polygon)
{
    int maxFrameX = frame[2].x;
    int minFrameX = frame[0].x;
    int maxFrameY = frame[1].y;
    int minFrameY = frame[0].y;
    int maxPolygonX = getMaxCoordinate(polygon, getX);
    int minPolygonX = getMinCoordinate(polygon, getX);
    int maxPolygonY = getMaxCoordinate(polygon, getY);
    int minPolygonY = getMinCoordinate(polygon, getY);
    bool isOverMax = maxPolygonX <= maxFrameX && maxPolygonY <= maxFrameY;
    bool isLessMin = minPolygonX >= minFrameX && minPolygonY >= minFrameY;
    if (isOverMax && isLessMin)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void inframe(std::vector< Polygon >& polygons, std::istream& input, std::ostream& output)
{
    Polygon polygon;
    input >> polygon;
    if (!input)
    {
        throw std::invalid_argument("");
    }
    else
    {
        std::vector< Point > frame = getFrame(polygons);

        output << (isInFrame(frame, polygon) ? "<TRUE>" : "<FALSE>") << "\n";
    }
}
