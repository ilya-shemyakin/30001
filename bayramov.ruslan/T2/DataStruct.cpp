#include "DataStruct.h"
#include "DataStruct.h"
#include <cmath>

using std::string;
using std::istream;
using std::ostream;
using std::cout;
using std::endl;

namespace nspace
{

    istream& operator>>(istream& in, DelimiterIO&& dest)
    {
        istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        char c = '0';
        in >> c;
        if (in and c != dest.exp)
        {
            in.setstate(std::ios::failbit);
        }
        return in;
    }

    istream& operator>>(istream& in, ULLLitIO&& dest)
    {
        istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        return in >> dest.ref >> DelimiterIO{ 'u' } >> DelimiterIO{ 'l' } >> DelimiterIO{ 'l' };
    }

    istream& operator>>(istream& in, ULLBinIO&& dest)
    {
        istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        

        string ullBin = "";
        std::getline(in >> DelimiterIO{ '0' } >> DelimiterIO{ 'b' } >> DelimiterIO{ '0' }, ullBin, ':');

        bool isTrue = true;
        unsigned long long number = 0;
        for (int i = 0; i < ullBin.length() and isTrue; ++i)
        {
            if (ullBin[i] == '1')
            {
                number += pow(2, ullBin.length() - i - 1);
            }
            else if (ullBin[i] == '0')
            {
                ;
            }
            else
            {
                isTrue = false;
                in.setstate(std::ios::failbit);
            }
        }
        
        dest.ref = number; // (:key1 89ull:key2 0b01111:key3 "Data":)

        return in;
    }

    std::istream& operator>>(std::istream& in, StringIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry) {
            return in;
        }
        return std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"');
    }


    istream& operator>>(istream& in, DataStruct& dest)
    {
        istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        DataStruct input;
        {
            using skip = DelimiterIO;
            using ullLit = ULLLitIO;
            using ullBin = ULLBinIO;
            using str = StringIO;

            in >> skip{ '(' };
            in >> skip{ ':' };
            int numberOfKey = 0;
            for (int i = 0; i < 3; ++i)
            {
                in >> skip{ 'k' };
                in >> skip{ 'e' };
                in >> skip{ 'y' };

                in >> numberOfKey;
                if (numberOfKey == 1)
                {
                    in >> ullLit{ input.key1 } >> skip{ ':' };
                }
                else if (numberOfKey == 2)
                {                    
                    in >> ullBin{ input.key2 };
                }
                else if (numberOfKey == 3)
                {
                    in >> str{ input.key3 } >> skip{ ':' };
                }
                else
                {
                    in.setstate(std::ios::failbit);
                }
            }
            in >> skip{ ')' };
        }
        if (in)
        {
            dest = input;
        }
        return in;
    }

    ostream& operator<<(ostream& out, const DataStruct& src)
    {
        ostream::sentry sentry(out);
        if (!sentry)
        {
            return out;
        }
        iofmtguard fmtguard(out);
        out << "(:";
        out << "key1 " << src.key1 << "ull:";

        string temp = "";
        unsigned long long int tempInt = src.key2;
        if (tempInt == 0)
        {
            temp = "0";
        }
        else
        {
            while (tempInt > 0)
            {
                if (tempInt % 2 == 0)
                {
                    temp = "0" + temp;
                }
                else
                {
                    temp = "1" + temp;
                }
                tempInt /= 2;
            }
        }
        
        out << "key2 " << "0b0" + temp + ':';
        out << "key3 \"" << src.key3;
        out << "\":)";
        return out;
    }

    iofmtguard::iofmtguard(std::basic_ios< char >& s) :
        s_(s),
        fill_(s.fill()),
        precision_(s.precision()),
        fmt_(s.flags())
    {}

    iofmtguard::~iofmtguard()
    {
        s_.fill(fill_);
        s_.precision(precision_);
        s_.flags(fmt_);
    }
}
