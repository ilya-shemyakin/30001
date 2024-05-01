#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <iterator>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "DataStruct.h"

int main()
{
    using namespace nspace;

    setlocale(LC_ALL, "RU");

    std::vector<DataStruct> vectorData;
    while (std::cin.good())
    {
        std::copy(
            std::istream_iterator<DataStruct>(std::cin),
            std::istream_iterator<DataStruct>(),
            std::back_inserter(vectorData)
        );
        if (std::cin.fail() && !std::cin.eof())
        {
            std::cin.clear();
            std::cin.ignore();
        }
    }
    std::sort(vectorData.begin(), vectorData.end(), [](const DataStruct& first, const DataStruct& second)
        {
            if (first.key1 != second.key1)
            {
                return second.key1 > first.key1;
            }
            if (first.key2 != second.key2)
            {
                return second.key2 > first.key2;
            }
            return second.key3.length() > first.key3.length();
        }
    );
    std::copy(
        std::begin(vectorData),
        std::end(vectorData),
        std::ostream_iterator< DataStruct >(std::cout, "\n")
    );
    return 0;
}