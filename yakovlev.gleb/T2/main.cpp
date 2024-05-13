#include "DataStruct.h"

int main() {
    std::vector< DataStruct > data;
    for (int i = 0; std::cin.good(); i++) {
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
    std::sort(data.begin(), data.end(), [](const DataStruct& left, const DataStruct& right) {
        return (left.key1 != right.key1) ? (left.key1 < right.key1) :
            (left.key2 != right.key2 ? left.key2 < right.key2 :
            left.key3.length() < right.key3.length());
    });
    std::copy(
        std::begin(data),
        std::end(data),
        std::ostream_iterator< DataStruct >(std::cout, "\n")
    );

    return 0;
}
