#include "DataStruct.h"
#include <iterator>
#include <vector>
#include <algorithm>
int main()
{
    using nspace::DataStruct;
    using nspace::sortFunction;
    std::vector< DataStruct > data;

    while (std::cin.good())
    {
        std::copy(
                std::istream_iterator<DataStruct>(std::cin),
                std::istream_iterator<DataStruct>(),
                std::back_inserter(data)
        );
        if (std::cin.fail() && !std::cin.eof())
        {
            std::cin.clear();
            std::cin.ignore();
        }
    }
    std::sort(data.begin(), data.end(), sortFunction);
    std::copy(
            std::begin(data),
            std::end(data),
            std::ostream_iterator< DataStruct >(std::cout, "\n")
    );
}
