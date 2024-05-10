#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H

#include <cassert>
#include <cmath>
#include <iostream>
#include <string>
#include <iterator>
#include <vector>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include "Iofmtguard.h"


struct DataStruct {
    double key1;
    unsigned long long int key2;
    std::string key3;
};

struct DelimiterIO {
    char exp;
};

struct DblSciIO {
    double& ref;
};

struct StringIO {
    std::string& ref;
};

struct LabelIO {
    std::string exp;
};

struct UllBinIO {
    unsigned long long int& ref;
};

std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
std::istream& operator>>(std::istream& in, DblSciIO&& dest);
std::istream& operator>>(std::istream& in, StringIO&& dest);
std::istream& operator>>(std::istream& in, LabelIO&& dest);
std::istream& operator>>(std::istream& in, UllBinIO&& dest);
std::istream& operator>>(std::istream& in, DataStruct& dest);
std::ostream& operator<<(std::ostream& out, const DataStruct& dest);

#endif
