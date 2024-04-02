#include "DataStruct.h"

bool isCorrectDouble(const std::string& sourse)
{
    bool result = true;
    int last = sourse.length() - 1;

    if ((last >= 1 && sourse[last] != 'd' && sourse[last] != 'D')
        || (last >= 1 && sourse[last - 1] == '.')
        || last < 1)
    {
        result = false;
    }
    else
    {
        int nDots = 0;
        for (int i = 0; i < last && result; ++i)
        {
            if (not((sourse[i] >= '0' && sourse[i] <= '9')
                || (sourse[i] == '.' && nDots++ == 0)))
            {
                result = false;
            }
        }
    }
    return result;
}



bool isCorrectULL(const std::string& sourse)
{
    bool result = true;
    int size = sourse.length();
    if (size > 2 &&
        ((sourse[0] == '0' && sourse[1] == 'x') ||
            (sourse[0] == '0' && sourse[1] == 'X')))
    {
        for (int i = 2; i < size && result; ++i)
        {
            if (not((sourse[i] >= '0' && sourse[i] <= '9')
                || (sourse[i] >= 'a' && sourse[i] <= 'f')
                || (sourse[i] >= 'A' && sourse[i] <= 'F')))
            {
                result = false;
            }
        }
    }
    else
    {
        result = false;
    }
    return result;
}

//формат ввода (:key1 50.0d:key2 0xFFFA:key3 "Data":)
std::istream& operator>>(std::istream& in, DataStruct& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    Iofmtguard fmtguard(in);
    in.ignore(2);
    std::string nKey;
    std::string value;
    for (int i = 0; i < 3; ++i)
    {
        std::getline(in, nKey, ' ');
        if (nKey == "key1")
        {
            std::getline(in, value, ':');
            std::istringstream valueStream(value);
            if (isCorrectDouble(value))
            {
                valueStream >> dest.key1;
            }
            else
            {
                in.ignore(1000, '\n');
            }
        }
        else if (nKey == "key2")
        {
            std::getline(in, value, ':');
            std::istringstream valueStream(value);
            if (isCorrectULL(value))
            {
                valueStream >> std::hex >> dest.key2;
            }
            else
            {
                in.ignore(1000, '\n');
            }
        }
        else if (nKey == "key3")
        {
            in.ignore(1);
            std::getline(in, value, '"');
            dest.key3 = (std::string("\"") + value + std::string("\""));
            in.ignore(1);
        }
    }
    in.ignore(1);
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
    out << ":key3 " << sourse.key3;
    out << ":)";
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
