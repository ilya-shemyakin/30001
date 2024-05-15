#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <iterator>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "DataStruct.h"
using std::cout;
using std::endl;
int main()
{
    using namespace nspace;
    setlocale(LC_ALL, "rus");
    std::vector<DataStruct> data;
    while (std::cin.good())
    {
        std::copy(
            std::istream_iterator< DataStruct >(std::cin),
            std::istream_iterator< DataStruct >(),
            std::back_inserter(data)
        );
        if (!std::cin.eof() && std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore();
        }
    }
    std::sort(data.begin(), data.end(), [](const DataStruct& first, const DataStruct& second)
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
        std::begin(data),
        std::end(data),
        std::ostream_iterator< DataStruct >(std::cout, "\n")
    );
    cout << endl;
}
