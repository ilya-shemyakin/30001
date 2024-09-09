#include <vector>
#include <algorithm>
#include <iterator>
#include "DataStruct.h"

int main() {
    using nspace::DataStruct;
    std::vector<DataStruct> data;
    while (std::cin.good()) {
        std::copy(
                std::istream_iterator<DataStruct>(std::cin),
                std::istream_iterator<DataStruct>(),
                std::back_inserter(data)
        );
        if (std::cin.fail() && !std::cin.eof()) {
            std::cin.clear();
            std::cin.ignore();
        }
    }
}