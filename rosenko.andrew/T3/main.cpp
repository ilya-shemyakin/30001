#include <fstream>
#include <map>

#include "Polygon.h"
#include "Commands.h"

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        return 1;
    }

    std::ifstream input(argv[1]);
    if (!input)
    {
        return 1;
    }

    std::vector< Polygon > polygons;

    int i = 0;
    while (!input.eof())
    {
        std::copy(
            std::istream_iterator< Polygon >(input),
            std::istream_iterator< Polygon >(),
            std::back_inserter(polygons)
        );

        if (input.fail() && !input.eof())
        {
            input.clear();
            input.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
        }
        i++;
    }

    std::map< std::string, std::function < void(std::vector< Polygon >&, std::istream&, std::ostream&) > > commands;
    {
        using namespace std::placeholders;
        commands["AREA"] = std::bind(area, _1, _2, _3);
        commands["MAX"] = std::bind(max, _1, _2, _3);
        commands["MIN"] = std::bind(min, _1, _2, _3);
        commands["COUNT"] = std::bind(count, _1, _2, _3);
        commands["RMECHO"] = std::bind(rmecho, _1, _2, _3);
        commands["INFRAME"] = std::bind(inframe, _1, _2, _3);
    }

    std::string cmd;
    while (!std::cin.eof())
    {
        try
        {
            std::cin >> cmd;

            if (std::cin.eof())
            {
                break;
            }

            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

            commands.at(cmd)(polygons, std::cin, std::cout);

        }
        catch (...)
        {
            std::cout << "<INVALID COMMAND>" << '\n';
        }
    }

    return 0;
}