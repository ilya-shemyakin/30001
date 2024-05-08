#include <iostream>
#include <fstream>
#include "Polygon.h"


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

    return 0;
}
