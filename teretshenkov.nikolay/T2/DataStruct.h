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


struct DelimiterIO
{
    char exp;
};

struct UllHexIO
{
    unsigned long long &ref;
};

struct DblLitIO
{
    double &ref;
};

struct StringIO
{
    std::string &ref;
};

struct DelStrIO
{
    std::string exp;
};

std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
std::istream& operator>>(std::istream& in, UllHexIO&& dest);
std::istream& operator>>(std::istream& in, DblLitIO&& dest);
std::istream& operator>>(std::istream& in, StringIO&& dest);
std::istream& operator>>(std::istream& in, DelStrIO&& dest);
std::istream& operator>>(std::istream& in, DataStruct& dest);
std::ostream& operator<<(std::ostream& out, const DataStruct& sourse);
bool sortData(const DataStruct& first, const DataStruct& second);


#endif // !DATA_STRUCT_H
