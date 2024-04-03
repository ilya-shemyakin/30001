#include "DataStruct.h"

std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    char symb = '0';
    in >> symb;
    if (in && (std::tolower(symb) != std::tolower(dest.exp)))
    {
        in.setstate(std::ios::failbit);
    }
    return in;
}

std::istream& operator>>(std::istream& in, UllHexIO&& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }

    return in >> std::hex >> dest.ref;
}


std::istream& operator>>(std::istream& in, DblLitIO&& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }

    in >> dest.ref >> DelimiterIO{ 'd' };
    if (!in)
    {
        in.setstate(std::ios::failbit);
    }
    return in;
}


std::istream& operator>>(std::istream& in, StringIO&& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    return std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"');
}

std::istream& operator>>(std::istream& in, DelStrIO&& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    size_t i = 0;
    while (dest.exp[i] != '\0')
    {
        in >> DelimiterIO({ dest.exp[i++] });
    }
    return in;
}

//формат ввода (:key1 50.0d:key2 0xFFFA:key3 "Data":)
std::istream& operator>>(std::istream& in, DataStruct& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    Iofmtguard fmtguard(in);//

    DataStruct temp;
    {
        in >> DelStrIO({"(:"});
        int nKey = 0;
        for (int i = 0; i < 3; ++i)
        {
            in >> DelStrIO({"key"}) >> nKey;
            if (nKey == 1)
            {
                in >> DblLitIO{temp.key1};
            }
            else if (nKey == 2)
            {
                in >> std::hex >> UllHexIO{ temp.key2 } >> std::dec;
            }
            else if (nKey == 3)
            {
                in >> StringIO{temp.key3};
            }
            else
            {
                in.setstate(std::ios::failbit);
            }
            in >> DelimiterIO{ ':' };
        }
        in >> DelimiterIO{ ')' };
    }
    if (in)
    {
        dest = temp;
    }
    return in;
}


//формат вывода (:key1 50.0d:key2 0xFFFA:key3 "Data":)
std::ostream& operator<<(std::ostream& out, const DataStruct& sourse)
{
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
        return out;
    }
    Iofmtguard fmtguard(out);
    out << "(:";
    out << "key1 " << std::fixed << std::setprecision(1) << sourse.key1 << "d:";
    out << "key2 0x" << std::hex << std::uppercase << sourse.key2 << std::nouppercase;
    out << ":key3 \"" << sourse.key3;
    out << "\":)";
    return out;
}

bool sortData(const DataStruct& first, const DataStruct& second)
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
