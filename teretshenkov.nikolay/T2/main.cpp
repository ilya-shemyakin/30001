#include "DataStruct.h"

int main()
{
    std::vector<DataStruct> dataVector;
    while (std::cin.good())
    {
        std::copy(
            std::istream_iterator<DataStruct>(std::cin),
            std::istream_iterator<DataStruct>(),
            std::back_inserter(dataVector)
        );
        if (std::cin.fail() && !std::cin.eof())
        {
            std::cin.clear();
            std::cin.ignore();
        }
    }
    std::sort(dataVector.begin(), dataVector.end(), sortData);
    std::copy(
        std::begin(dataVector),
        std::end(dataVector),
        std::ostream_iterator< DataStruct >(std::cout, "\n")
    );
    return 0;
}