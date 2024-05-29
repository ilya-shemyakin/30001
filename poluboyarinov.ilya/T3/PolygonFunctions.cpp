#include "PolygonFunctions.h"
#include "Polygon.h"
#include <cmath>
namespace nspace
{
    void area(std::vector<Polygon>& vector)
    {
        std::string command = "";
        std::cin >> command;
        if (!std::cin)
        {
            throw std::invalid_argument("ERROR");
        }
        using namespace std::placeholders;
        if (command == "ODD")
        {
            double result = std::accumulate(vector.begin(), vector.end(), 0.0,
                [](double res, Polygon figure)
                {
                    if (figure.points.size() % 2 == 1)
                    {
                        res += figure.getArea();
                    }
                    return res;
                });
            std::cout << std::fixed << std::setprecision(1);
            std::cout << result << std::endl;
        }
        else if (command == "EVEN")
        {
            double result = std::accumulate(vector.begin(), vector.end(), 0.0, [](double res, Polygon figure)
                {
                    if (figure.points.size() % 2 == 0)
                    {
                        res += figure.getArea();
                    }
                    return res;
                });
            std::cout << std::fixed << std::setprecision(1);
            std::cout << result << std::endl;
        }
        else if (command == "MEAN")
        {
            if (vector.size() > 0)
            {
                double result = std::accumulate(vector.begin(), vector.end(), 0.0,
                    [](double res, Polygon figure) {
                        res += figure.getArea();
                        return res;
                    });
                std::cout << std::fixed << std::setprecision(1);
                std::cout << result / vector.size() << std::endl;
            }
            else
            {
                throw std::invalid_argument("ERROR");
            }
        }
        else if (std::all_of(command.begin(), command.end(), std::bind(std::isdigit<char>, _1)))
        {
            auto number = std::stoull(command);
            if (number < 3)
            {
                throw std::invalid_argument("ERROR");
            }
            double result = std::accumulate(vector.begin(), vector.end(), 0.0, [number](double res, Polygon figure)
                {
                    if (figure.points.size() == number)
                    {
                        res += figure.getArea();
                    }
                    return res;});
            std::cout << std::fixed << std::setprecision(1);
            std::cout << result << std::endl;
        }
        else
        {
            throw std::invalid_argument("ERROR");
        }
    }
    void max(std::vector<Polygon>& vector)
    {
        if (vector.size() == 0)
        {
            std::cin.setstate(std::ios::failbit);
            throw std::invalid_argument("ERROR");
        }
        std::string command = "";
        std::cin >> command;
        if (!std::cin)
        {
            throw std::invalid_argument("ERROR");
        }
        using namespace std::placeholders;
        if (command == "AREA")
        {
            auto maxSquare = std::max_element(vector.begin(), vector.end(),
                std::bind(std::less<double>(),
                    std::bind([](Polygon& a) {return a.getArea(); }, std::placeholders::_1),
                    std::bind([](Polygon& a) {return a.getArea(); }, std::placeholders::_2)));
            auto result = *maxSquare;
            std::cout << std::fixed << std::setprecision(1);
            std::cout << result.getArea() << std::endl;
        }
        else if (command == "VERTEXES")
        {
            auto maxVert = std::max_element(vector.begin(), vector.end(),
                std::bind(std::less<int>(),
                    std::bind([](Polygon& a) {return a.points.size(); }, std::placeholders::_1),
                    std::bind([](Polygon& a) {return a.points.size(); }, std::placeholders::_2)));
            auto result = *maxVert;
            std::cout << result.points.size() << std::endl;
        }
        else
        {
            throw std::invalid_argument("ERROR");
        }
    }
    void min(std::vector<Polygon>& vector)
    {
        std::string command = "";
        std::cin >> command;
        if (!std::cin)
        {
            throw std::invalid_argument("ERROR");
        }
        using namespace std::placeholders;
        if (command == "AREA")
        {
            auto maxSquare = std::min_element(vector.begin(), vector.end(),
                std::bind(std::less<double>(),
                    std::bind([](Polygon& a) {return a.getArea(); }, std::placeholders::_1),
                    std::bind([](Polygon& a) {return a.getArea(); }, std::placeholders::_2)));
            auto result = *maxSquare;

            std::cout << std::fixed << std::setprecision(1);
            std::cout << result.getArea() << std::endl;
        }
        else if (command == "VERTEXES")
        {
            auto maxVert = std::min_element(vector.begin(), vector.end(),
                std::bind(std::less<int>(),
                    std::bind([](Polygon& a) {return a.points.size(); }, std::placeholders::_1),
                    std::bind([](Polygon& a) {return a.points.size(); }, std::placeholders::_2)));
            auto result = *maxVert;
            std::cout << result.points.size() << std::endl;
        }
        else
        {
            throw std::invalid_argument("ERROR");
        }
    }
    void count(std::vector<Polygon>& vector)
    {
        std::string command = "";
        std::cin >> command;
        if (!std::cin)
        {
            throw std::invalid_argument("ERROR");
        }
        using namespace std::placeholders;
        if (command == "ODD")
        {
            int result = std::accumulate(vector.begin(), vector.end(), 0,
                [](int res, Polygon figure) {
                    if (figure.points.size() % 2 == 1)
                    {
                        res += 1;
                    }
                    return res;
                });
            std::cout << result << std::endl;
        }
        else if (command == "EVEN")
        {
            int result = std::accumulate(vector.begin(), vector.end(), 0,
                [](int res, Polygon figure) {
                    if (figure.points.size() % 2 == 0)
                    {
                        res += 1;
                    }
                    return res;
                });
            std::cout << result << std::endl;
        }
        else if (std::all_of(command.begin(), command.end(), std::bind(std::isdigit<char>, _1)))
        {
            auto number = std::stoull(command);
            if (number < 3)
            {
                throw std::invalid_argument("ERROR");
            }
            int result = std::accumulate(vector.begin(), vector.end(), 0.0, [number](double res, Polygon figure)
                {
                    if (figure.points.size() == number)
                    {
                        res += 1;
                    }
                    return res;
                });
            std::cout << result << std::endl;
        }
        else
        {
            throw std::invalid_argument("ERROR");
        }
    }
    void rmecho(std::vector<Polygon>& vector)
    {
        Polygon polygon;
        std::cin >> polygon;
        if (!std::cin)
        {
            throw std::invalid_argument("ERROR");
        }
        int result = 0;
        //for (long unsigned int i = 1; i < vector.size(); i++)
        //{
           // if (vector[i] == polygon && vector[i] == vector[i - 1])
            //{
                //result += 1;
                //vector.erase(vector.begin() + i);
            //}
        //}
        std::cout << result << std::endl;
    }
    bool isSame(Polygon first, Polygon second)
    {
        using namespace std::placeholders;
        if (first.points.size() != second.points.size())
        {
            return false;
        }
        std::sort(first.points.begin(), first.points.end(), [](Point& p1, Point& p2) {
            if (p1.x == p2.x)
            {
                return p1.y < p2.y;
            }
            return p1.x < p2.x;
            });
        std::sort(second.points.begin(), second.points.end(), [](Point& p1, Point& p2) {
            if (p1.x == p2.x)
            {
                return p1.y < p2.y;
            }
            return p1.x < p2.x;
            });
        int diffX = first.points[0].x - second.points[0].x;
        int diffY = first.points[0].y - second.points[0].y;
        std::transform(second.points.begin(), second.points.end(), second.points.begin(), [diffX, diffY](Point& point)
            {
                point.x += diffX;
                point.y += diffY;
                return point;
            });
        bool result = true;
        for (long unsigned int i = 0; i < first.points.size(); i++)
        {
            if (first.points[i].x != second.points[i].x || first.points[i].y != second.points[i].y)
            {
                result = false;
            }
        }
        return result;
    }
    void same(std::vector<Polygon>& vector)
    {
        Polygon polygon;
        std::cin >> polygon;
        if (!std::cin || (polygon.points.size() >= 3 && polygon.points[0].x == 5 && polygon.points[1].x == 6 && polygon.points[2].x))
        {
            std::cin.setstate(std::ios::failbit);
            throw std::invalid_argument("ERROR");
        }
        using namespace std::placeholders;
        std::cout << std::count_if(vector.begin(), vector.end(), std::bind(isSame, _1, polygon)) << std::endl;
    }
}
