#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#include <iostream>
#include <string>
namespace rosenko
{
    struct DataStruct
    {
        double key1;
        long long key2;
        std::string key3;
    };
    std::istream& operator>>(std::istream& in, DataStruct& dest);
    std::ostream& operator<<(std::ostream& out, const DataStruct& dest);
    bool compare(DataStruct& lhs, DataStruct& rhs);
}

#endif