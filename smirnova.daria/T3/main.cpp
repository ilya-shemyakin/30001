#include <iostream>
#include <string>
#include <iterator>
#include <vector>
#include <list>
#include <iomanip>
#include <algorithm>
#include <functional>
#include <numeric>
#include <complex>
#include "commandOfFigure.h"
#include <fstream>
#include <map>
#include <limits>
#include <exception>

int main()
{
    std::vector< Polygon > polygons;

    using input_it_t = std::istream_iterator< Polygon >;

    using namespace std::placeholders;
    std::map< std::string, std::function< void(std::istream&, std::ostream&, const std::vector< Polygon >&) > > commands;
    commands["AREA"] = std::bind(area, std::cref(polygons), _1, _2);
    commands["MAX"] = std::bind(max, std::cref(polygons), _1, _2);
    commands["MIN"] = std::bind(min, std::cref(polygons), _1, _2);
    commands["COUNT"] = std::bind(area, std::cref(polygons), _1, _2);
    commands["RMECHO"] = std::bind(rmecho, std::ref(polygons), _1, _2);
    commands["INTERSECTIONS"] = std::bind(intersections, std::cref(polygons), _1, _2);

    std::string command = "";
    while (std::cin >> command)
    {
        try
        {
            commands.at(command)(std::cin, std::cout, polygons);
            std::cout << '\n';
        }
        catch (const std::exception&)
        {
            std::cout << ERROR_IN_COMMAND << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
        }
    }

    return 0;
}
