#ifndef INPOUTTYPES_H
#define INPOUTTYPES_H

#include <string>
#include <iostream>

struct DelimiterIO
{
    char exp;
};
struct DblI
{
    double& num;
};
struct DblO
{
    const double num;
};
struct SllIO
{
    long long& num;
};
struct StringIO
{
    std::string& exp;
};
struct LabelIO
{
    std::string exp;
};
std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
std::istream& operator>>(std::istream& in, LabelIO&& dest);
std::istream& operator>>(std::istream& in, StringIO&& dest);
std::istream& operator>>(std::istream& in, SllIO&& dest);
std::istream& operator>>(std::istream& in, DblI&& dest);
std::ostream& operator<<(std::ostream& out, const DblO&& dest);


#endif
