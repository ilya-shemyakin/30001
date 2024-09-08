#include "DataStruct.h"
namespace nspace {
    std::istream &operator>>(std::istream &in, DelimiterIO &&dest)
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

    std::istream &operator>>(std::istream &in, StringIO &&dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        return std::getline(in >> DelimiterIO{ '"'}, dest.ref, '"');
    }

    std::istream &operator>>(std::istream &in, DelStrIO &&dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        size_t i = 0;
        while (dest.exp[i] != '\0')
        {
            in >> DelimiterIO({dest.exp[i++]});
        }
        return in;
    }

    std::istream &operator>>(std::istream &in, ChrLitIO &&dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }

        in >> DelimiterIO{'\''} >> dest.ref >> DelimiterIO{'\''};
        if (!in)
        {
            in.setstate(std::ios::failbit);
        }
        return in;
    }

    std::istream &operator>>(std::istream &in, RatLSPIO &&dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        return in >> DelStrIO{"(:N"} >> dest.ref.first >> DelStrIO{":D"}
                  >> dest.ref.second >> DelStrIO{":)"};
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
            using sepStr = DelStrIO;
            using chrLit = ChrLitIO;
            using ratLSP = RatLSPIO;
            using str = StringIO;
            in >> sepStr({"(:"});
            int keyNumber = 0;
            for (size_t i = 0; i < 3 ; i++) {
                in >> sepStr({"key"}) >> keyNumber;
                if (keyNumber == 1)
                {
                    in >> chrLit{ input.key1 };
                }
                else if (keyNumber == 2)
                {
                    in >> ratLSP {input.key2};
                }
                else if (keyNumber == 3)
                {
                    in >> str{input.key3};
                }
                else
                {
                    in.setstate(std::ios::failbit);
                }
                in >> sep{ ':'};
            }
            in >> sep{ ')'};
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
        out << "(:key1 " << src.key1;
        out << ":key2 (:N " << src.key2.first << ":D " << src.key2.second << ":)";
        out << ":key3 \"" << src.key3 << "\":)";
        return out;
    }
}