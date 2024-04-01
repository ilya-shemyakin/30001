#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <limits>

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

    struct UllOctIO
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

    class iofmtguard
    {
    public:
        iofmtguard(std::basic_ios< char > &s);
        ~iofmtguard();
    private:
        std::basic_ios< char > &s_;
        char fill_;
        std::streamsize precision_;
        std::basic_ios< char >::fmtflags fmt_;
    };

    std::istream &operator>>(std::istream &in, DelimiterIO &&dest);
    std::istream &operator>>(std::istream &in, UllOctIO &&dest);
    std::istream &operator>>(std::istream &in, UllLitIO &&dest);
    std::istream &operator>>(std::istream &in, StringIO &&dest);
    std::istream &operator>>(std::istream &in, LabelIO &&dest);
    std::istream &operator>>(std::istream &in, DataStruct &dest);
    std::ostream &operator<<(std::ostream &out, const DataStruct &dest);
}

int main()
{
    using nspace::DataStruct;
    std::vector< DataStruct > data;
    while (std::cin.good())
    {
        std::string input;
        std::getline(std::cin, input);
        std::cout << input;
        std::istringstream inputStream(input);
        std::copy(
                std::istream_iterator< DataStruct >(inputStream),
                std::istream_iterator< DataStruct >(),
                std::back_inserter(data)
        );
    }


    std::cout << "Data:\n";
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
        if (in && (c != dest.exp))
        {
            in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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

        in >> dest.ref >> DelimiterIO{ 'u' } >> DelimiterIO{ 'l' } >> DelimiterIO{ 'l' };
        if (!in)
        {
            in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        return in;
    }
    std::istream &operator>>(std::istream &in, UllOctIO &&dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        return in >> std::oct >> dest.ref;
    }
    std::istream &operator>>(std::istream &in, StringIO &&dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        return std::getline(in >> DelimiterIO{ '"'}, dest.ref, '"');
    }
    std::istream &operator>>(std::istream &in, LabelIO &&dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        std::string data = "";
        if ((in >> data) && (data != dest.exp))
        {
            std::cerr << data << " ERROR";
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
            using sep = DelimiterIO;
            using label = LabelIO;
            using ullLit = UllLitIO;
            using ullOct = UllOctIO;
            using str = StringIO;
            in >> sep{ '(' } >> sep { ':'};
            in >> label{ "key1" } >> ullLit { input.key1 };
            in >> sep{ ':' };
            in >> label{ "key2" } >> ullOct { input.key2 };
            in >> sep{ ':' };
            in >> label{ "key3" } >> str { input.key3 };
            in >> sep{ ':' } >> sep { ')'};
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
        out << "(:key1 " << src.key1 << "ull";
        out << ":key2 " << std::oct << std::showbase << src.key2;
        out << ":key3 \"" << src.key3 << "\":)";
        return out;
    }

    iofmtguard::iofmtguard(std::basic_ios< char > &s) :
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
