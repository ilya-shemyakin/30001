#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H

#include <string>
#include <iterator>
#include <vector>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include "Iofmtguard.h"

struct DataStruct
{
    double key1;
    unsigned long long key2;
    std::string key3;
};

bool isCorrectDouble(const std::string& sourse);
bool isCorrectULL(const std::string& sourse);
std::istream& operator>>(std::istream& in, DataStruct& dest);
std::ostream& operator<<(std::ostream& out, const DataStruct& sourse);
bool sortData(const DataStruct& first, const DataStruct& second);

#endif // !DATA_STRUCT_H
