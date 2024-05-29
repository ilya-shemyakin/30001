#include <iostream>
#include <fstream>
#include "Polygon.h"
#include "PolygonFunctions.h"

/*
3 (0;0) (0;2) (2;0)
4 (0;1) (1;1) (1;0) (0;0)
5 (0;0) (1;0) (2;1) (1;2) (0;2)
3 (4;3) (4;2) (3;2)
4 (0;0) (1;0) (1;1) (0;1)
3 (0;0) (1;1) (0;1)
4 (1;1) (2;1) (2;2) (1;2)
SAME 4 (-1;-1) (-1;0) (0;0) (0;-1)
SAME 3 (10;10) (11;11) (10;11)
SAME 3 (10;10) (10;11) (11;10)

*/

int main(int countOfArg, char** name)
{
    if (countOfArg < 2)
    {
        return 1;
    }

    std::ifstream inpFile(name[1]);
    if (!inpFile)
    {
        return 1;
    }

    std::vector<nspace::Polygon> polygons;

    while (std::cin.good())
    {
        std::copy(
            std::istream_iterator<nspace::Polygon>(std::cin),
            std::istream_iterator<nspace::Polygon>(),
            std::back_inserter(polygons)
        );
        if (std::cin.fail() && !std::cin.eof())
        {
            std::cin.clear();
            std::cin.ignore();
        }
    }

    std::cin.clear();

    std::string command;
    while (!std::cin.eof())
    {
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        try
        {
            std::cin >> command;
            if (std::cin.eof())
            {
                break;
            }
            else if (command == "AREA")
            {
                area(polygons);
            }
            else if (command == "MAX")
            {
                max(polygons);
            }
            else if (command == "MIN")
            {
                min(polygons);
            }
            else if (command == "COUNT")
            {
                count(polygons);
            }
            else if (command == "RMECHO")
            {
                rmecho(polygons);
            }
            else if (command == "SAME")
            {
                same(polygons);
            }
            else
            {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw std::invalid_argument("");
            }
        }
        catch (...)
        {
            std::cout << "<INVALID COMMAND>" << '\n';
        }
    }
    
    return 0;
}
