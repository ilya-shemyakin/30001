#include <iostream>
#include <fstream>
#include "Polygon.h"
#include "PolygonFunctions.h"
int main(int countOfArg, char** name)
{
    std::cout << "hello\n";
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
    while (inpFile.good())
    {
        std::copy(
            std::istream_iterator<nspace::Polygon>(inpFile),
            std::istream_iterator<nspace::Polygon>(),
            std::back_inserter(polygons)
        );
        if (inpFile.fail() && !inpFile.eof())
        {
            inpFile.clear();
            inpFile.ignore();
        }
    }
    std::cout << polygons.size() << "\n";
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
