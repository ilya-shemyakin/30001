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