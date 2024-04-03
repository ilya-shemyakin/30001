#include <vector>
#include <algorithm>
#include <sstream>
#include <iterator>
#include "DataStruct.h"

int main()
{
    using nspace::DataStruct;
    std::vector< DataStruct > data;
    std::copy(
            std::istream_iterator< DataStruct >(std::cin),
            std::istream_iterator< DataStruct >(),
            std::back_inserter(data)
    );
    std::sort(data.begin(), data.end(), [](const DataStruct& a, const DataStruct& b) {
        if (a.key1 != b.key1)
        {
            return a.key1 < b.key1;
        }
        else if (a.key2 != b.key2)
        {
            return a.key2 < b.key2;
        }
        return a.key3 < b.key3;
    });
    std::copy(
            std::begin(data),
            std::end(data),
            std::ostream_iterator< DataStruct >(std::cout, "\n")
    );
}
