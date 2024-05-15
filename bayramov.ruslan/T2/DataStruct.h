#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H

#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <iterator>
#include <vector>
#include <iomanip>
using std::string;
using std::istream;
using std::basic_ios;
using std::streamsize;
using std::ostream;
namespace nspace
{
    struct DataStruct
    {
        unsigned long long int key1;
        unsigned long long int key2;
        string key3;
    };
    struct DelimiterIO
    {
        char exp;
    };
    struct ULLLitIO
    {
        unsigned long long int& ref;
    };
    struct ULLBinIO
    {
        unsigned long long int& ref;
    };
    struct StringIO
    {
        string& ref;
    };
    class iofmtguard
    {
    public:
        iofmtguard(std::basic_ios< char >& s);
        ~iofmtguard();
    private:
        basic_ios< char >& s_;
        char fill_;
        streamsize precision_;
        basic_ios< char >::fmtflags fmt_;
    };
    istream& operator>>(istream& in, DelimiterIO&& dest);
    istream& operator>>(istream& in, ULLLitIO&& dest);
    istream& operator>>(istream& in, ULLBinIO&& dest);
    istream& operator>>(istream& in, DataStruct& dest);
    ostream& operator<<(ostream& out, const DataStruct& dest);
}
#endif
