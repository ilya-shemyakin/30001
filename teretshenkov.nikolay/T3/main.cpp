#include <fstream>
#include <map>

#include "polygonCommands.h"

int main(int nArguments, char** file)
{
    if (nArguments < 2)
    {
        return 1;
    }

    std::ifstream inputF(file[1]);
    if (!inputF)
    {
        return 1;
    }

    std::map < std::string, std::function <
        void(std::istream&, std::ostream&, std::vector < Polygon >&)>> commands;

    commands["PERMS"] = perms;
    commands["RIGHTSHAPES"] = rightShapes;
    commands["AREA"] = area;
    commands["MAX"] = max;
    commands["MIN"] = min;
    commands["COUNT"] = count;

    std::vector< Polygon > polygons;


    while (!inputF.eof())
    {
        std::copy(
            std::istream_iterator<Polygon>(inputF),
            std::istream_iterator<Polygon>(),
            std::back_inserter(polygons)
        );
        if (inputF.fail() && !inputF.eof())
        {
            inputF.clear();
//            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
            auto locCom = commands.find(command);
            if (locCom == commands.end()) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw std::invalid_argument("");
            }
            locCom->second(std::cin, std::cout, polygons);
        }
        catch (...)
        {
            std::cout << "<INVALID COMMAND>" << '\n';
        }
    }

    return 0;
}
