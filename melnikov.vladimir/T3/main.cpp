#include <iostream>
#include <fstream>
#include <functional>
#include "Polygon.h"
#include "Commands.h"
#include <map>

int main(int argc, char** argv) {
    using namespace melnikov;
    std::vector < Polygon > polygons;
    if (argc < 2)
    {
        return 1;
    }
    std::ifstream input(argv[1]);
    if (!input)
    {
        return 1;
    }
    std::map < std::string, std::function <
    void (std::istream &, std::ostream &, std::vector < Polygon > &)>> command;
    command["AREA"] = area;
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
    }
    std::string cmd;
    while (std::cin >> cmd)
    {
        auto func = command.find(cmd);
        func->second(std::cin, std::cout, polygons);
    }

    return 0;
}
