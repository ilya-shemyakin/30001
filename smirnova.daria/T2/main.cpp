
#include <iostream>
#include <sstream>
#include <string>
#include <iterator>
#include <vector>
#include <algorithm>
namespace nspace
{
    struct DataStruct
    {
        unsigned long long key1;
        unsigned long long key2;
        std::string key3;
    };

    struct DelimiterIO
    {
        char exp;
    };

    struct UllLitIO
    {
        unsigned long long &ref;
    };

    struct UllHexIO
    {
        unsigned long long &ref;
    };

    struct StringIO
    {
        std::string &ref;
    };

    struct LabelIO
    {
        std::string exp;
    };

    // scope guard для возврата состояния потока в первоначальное состояние
    class iofmtguard
    {
    public:
         iofmtguard(std::basic_ios< char > &s) noexcept;
        ~iofmtguard();
    private:
        std::basic_ios< char > &s_;
        char fill_;
        std::streamsize precision_;
        std::basic_ios< char >::fmtflags fmt_;
    };

    std::istream &operator>>(std::istream &in, DelimiterIO &&dest);
    std::istream &operator>>(std::istream &in, StringIO &&dest);
    std::istream &operator>>(std::istream &in, UllLitIO &&dest);
    std::istream &operator>>(std::istream &in, UllHexIO &&dest);
    std::istream &operator>>(std::istream &in, LabelIO &&dest);
    std::istream &operator>>(std::istream &in, DataStruct &dest);
    std::ostream &operator<<(std::ostream &out, const DataStruct &dest);

    bool sortFunction(const DataStruct& firstElement, const DataStruct& secondElement) {
        if (firstElement.key1 != secondElement.key1)
        {
            return secondElement.key1 > firstElement.key1;
        }
        if (firstElement.key2 != secondElement.key2)
        {
            return secondElement.key2 > firstElement.key2;
        }
        return secondElement.key3.length() > firstElement.key3.length();
    }

}

int main()
{
    using nspace::DataStruct;
    using nspace::sortFunction;
    std::vector< DataStruct > data;

    while (std::cin.good())
    {
        std::copy(
                std::istream_iterator<DataStruct>(std::cin),
                std::istream_iterator<DataStruct>(),
                std::back_inserter(data)
        );
        if (std::cin.fail() && !std::cin.eof())
        {
            std::cin.clear();
            std::cin.ignore();
        }
    }
    std::sort(data.begin(), data.end(), sortFunction);
    std::copy(
            std::begin(data),
            std::end(data),
            std::ostream_iterator< DataStruct >(std::cout, "\n")
    );
}

namespace nspace
{
    std::istream &operator>>(std::istream &in, DelimiterIO &&dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        char c = '0';
        in >> c;
        if (in and std::tolower(c) != std::tolower(dest.exp))
        {
            in.setstate(std::ios::failbit);
        }
        return in;
    }

    std::istream &operator>>(std::istream &in, UllLitIO &&dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        in >> dest.ref >> DelimiterIO{ 'u' } >> DelimiterIO{ 'l' }
        >> DelimiterIO{ 'l' };
        if (!in) {
            in.setstate(std::ios::failbit);
        }
        return in;
    }

    std::istream &operator>>(std::istream &in, UllHexIO &&dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        return in >> std::hex >> dest.ref;

    }

    std::istream &operator>>(std::istream &in, StringIO &&dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        return std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"');
    }

    std::istream &operator>>(std::istream &in, LabelIO &&dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        std::string DataStruct = "";
        if ((in >> StringIO{ DataStruct }) && (DataStruct != dest.exp))
        {
            in.setstate(std::ios::failbit);
        }
        return in;
    }

    std::istream &operator>>(std::istream &in, DataStruct &dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        DataStruct input;
        {
            std::string colon;
            using sep = DelimiterIO;
            using str = StringIO;
            using ullLit = UllLitIO;
            using ullHex = UllHexIO;
            std::string valueOfKey = "";
            const int MAX_COUNTER = 3;
            in >> sep{ '(' } >> sep{':'};
            for (int keyCounter = 0; keyCounter < MAX_COUNTER; keyCounter++)
            {
                in >> valueOfKey;
                if (valueOfKey == "key1")
                {
                    in >> ullLit{ input.key1 };
                }
                else if (valueOfKey == "key2")
                {
                    in >> ullHex{ input.key2 };
                }
                else if (valueOfKey == "key3") {
                    in >> str{input.key3};
                }
                else
                {
                    in.setstate(std::ios::failbit);
                }
                in >> sep{ ':' };
            }
            in >> sep{ ')' };
        }
        if (in)
        {
            dest = input;
        }
        return in;
    }

    std::ostream &operator<<(std::ostream &out, const DataStruct &src)
    {
        std::ostream::sentry sentry(out);
        if (!sentry)
        {
            return out;
        }
        iofmtguard fmtguard(out);
        out << "(" << ":key1 " << src.key1 << "ull";
        out << ":key2 0x" << std::uppercase << std::hex << src.key2 ;
        out << ":key3 \"" << src.key3 << "\":)";
        return out;
    }

    iofmtguard::iofmtguard(std::basic_ios< char > &s) noexcept:
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
