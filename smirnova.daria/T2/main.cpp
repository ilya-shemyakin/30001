#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <iterator>
#include <vector>
#include <iomanip>

namespace nspace
{
    struct Data
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
    bool sortFunction(const Data& firstElement, const Data& secondElement) {
        bool isResult = false;
        if (firstElement.key1 < secondElement.key1) {
            isResult = true;
        } else {
            isResult = false;
        }
        if (firstElement.key2 < secondElement.key2) {
            isResult = true;
        } else {
            isResult = false;
        }
        if (firstElement.key3.length() < secondElement.key3.length()) {
            isResult = true;
        } else {
            isResult = false;
        }
        return isResult;
    }

    // scope guard для возврата состояния потока в первоначальное состояние
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
    std::istream &operator>>(std::istream &in, StringIO &&dest);
    std::istream &operator>>(std::istream &in, UllLitIO &&dest);
    std::istream &operator>>(std::istream &in, UllHexIO &&dest);
    std::istream &operator>>(std::istream &in, LabelIO &&dest);
    std::istream &operator>>(std::istream &in, Data &dest);
    std::ostream &operator<<(std::ostream &out, const Data &dest);

}


int main()
{
    using nspace::Data;
    using nspace::sortFunction;

    std::vector< Data > data;
    std::istringstream iss("( \"key1\": 1ull, \"key2\": 1f )");
    std::copy(
            std::istream_iterator< Data >(iss),
            std::istream_iterator< Data >(),
            std::back_inserter(data)
    );
    std::sort(data.begin(), data.end(), sortFunction);
    std::copy(
            std::begin(data),
            std::end(data),
            std::ostream_iterator< Data >(std::cout, "\n")
    );



    //std::cout << "Data:\n";
    //std::sort(data.begin(), data.end(), );



    return 0;
}

namespace nspace
{
    bool isCorrectUllLit(const std::string& resultString) {
        bool isResult = false;
        for (int i = 0; i <= resultString.length(); i++) {
            if ('0' <= resultString[i] and resultString[i] <= '9') {
                isResult = true;
            } else {
                isResult = false;
            }
        }
        return isResult;
    }

    //0x(0-9/a-f)
    bool isCorrectUllHex(const std::string& resultString) {
        if (resultString[0] != '0' or (resultString[1] != 'x' or resultString[1] != 'X')) {
            return false;
        }
        bool isResult = false;
        for (int i = 2; i <= resultString.length(); i++) {
            if (('0' <= resultString[i] and resultString[i] <= '9') or
                ('a' <= resultString[i] and resultString[i] <= 'f') or
                ('A' <= resultString[i] and resultString[i] <= 'F')) {
                isResult = true;
            } else {
                isResult = false;
            }
        }
        return isResult;
    }

    std::istream &operator>>(std::istream &in, DelimiterIO &&dest)
    {
        // все перегрузки операторов ввода/вывода должны начинаться с проверки экземпляра класса sentry
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        char c = '0';
        in >> c;
        if (in && (c != dest.exp))
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
        return in >> dest.ref >> DelimiterIO{ 'u' } >> DelimiterIO{ 'l' }
        >> DelimiterIO{ 'l' };
    }

    std::istream &operator>>(std::istream &in, UllHexIO &&dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        //return in >> dest.ref >> DelimiterIO{ 'f' };
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
        std::string data = "";
        if ((in >> StringIO{ data }) && (data != dest.exp))
        {
            in.setstate(std::ios::failbit);
        }
        return in;
    }

    std::istream &operator>>(std::istream &in, Data &dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        Data input;
        {
            std::string colon;
            using sep = DelimiterIO;
            using label = LabelIO;
            using ullLit = UllLitIO;
            using ullHex = UllHexIO;
            using str = StringIO;
            std::string valueOfKey;
            in >> sep{ '(' };
            for (int keyCounter = 0; keyCounter < 3; keyCounter++)
            {
                std::istringstream strStream(colon);
                if (valueOfKey == "key1")
                {
                    if (isCorrectUllLit(colon))
                    {
                        strStream >> dest.key1;
                    }
                    else
                    {
                        in.ignore(100, '\n');
                    }
                }
                else if (valueOfKey == "key2")
                {
                    if (isCorrectUllHex(colon))
                    {
                        strStream >> std::hex >> dest.key2;
                    }
                    else
                    {
                        in.ignore(100, '\n');
                    }
                }
                else if (valueOfKey == "key3")
                {
                    in >> label{ "key3" } >> sep{ ':' } >> str{ input.key3 };
                }

            }
            in >> sep{ ':' } >> sep{ ')' };

        }
        if (in)
        {
            dest = input;
        }
        return in;
    }


    std::ostream &operator<<(std::ostream &out, const Data &src)
    {
        std::ostream::sentry sentry(out);
        if (!sentry)
        {
            return out;
        }
        iofmtguard fmtguard(out);
        out << "{ ";
        out << "\"key1\": " << std::fixed << std::setprecision(1) << src.key1 << "ull, ";
        out << "\"key2\": " << std::hex << src.key2 ;
        out << "\"key3\": " << src.key3 ;
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


