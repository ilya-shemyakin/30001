#include "DataStruct.h"
#include "DataStruct.h"

namespace nspace
{

    std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        char c = '0';
        in >> c;
        if (in && (std::tolower(c) != std::tolower(dest.exp)))
        {
            in.setstate(std::ios::failbit);
        }
        return in;
    }

    std::istream& operator>>(std::istream& in, DoubleLitIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        return in >> dest.ref >> DelimiterIO{ 'd' };
        if (!in)
        {
            in.setstate(std::ios::failbit);
        }
    }

    std::istream& operator>>(std::istream& in, SignedLongLongLitIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        std::string lit = "ll";
        return in >> dest.ref >> DelimiterIO{ 'l' } >> DelimiterIO{'l'};
        //if (!in)
        //{
        //    in.setstate(std::ios::failbit);
        //}
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

    std::istream& operator>>(std::istream& in, DataStruct& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        DataStruct input;
        {
            using skip = DelimiterIO;
            using skipKey = DelStrIO;
            using dbl = DoubleLitIO;
            using sll = SignedLongLongLitIO;
            using str = StringIO;

            in >> skip{ '(' };
            in >> skip{ ':' };
            int numberOfKey = 0;
            for (int i = 0; i < 3; i++)
            {
                in >> skipKey({ "key" });
                in >> numberOfKey;
                if (numberOfKey == 1)
                {
                    in >> dbl{ input.key1 };
                }
                else if (numberOfKey == 2)
                {
                    in >> sll{ input.key2 };
                }
                else if (numberOfKey == 3)
                {
                    in >> str{ input.key3 };
                }
                else
                {
                    in.setstate(std::ios::failbit);
                }
                in >> skip{ ':' };
            }
        }
        if (in)
        {
            dest = input;
        }
        return in;
    }

    std::ostream& operator<<(std::ostream& out, const DataStruct& src)
    {
        std::ostream::sentry sentry(out);
        if (!sentry)
        {
            return out;
        }
        iofmtguard fmtguard(out);
        out << "(:";
        out << "key1 " << std::fixed << std::setprecision(1) << src.key1 << "d:";
        out << "key2 " << src.key2 << "ll:";
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

