#ifndef T2_DATASTRUCT_H
#define T2_DATASTRUCT_H
#include <iostream>
namespace nspace {
    struct DataStruct {
        char key1;
        std::pair<long long, unsigned long long> key2;
        std::string key3;
    };
    struct DelimiterIO {
        char exp;
    };

    struct ChrLitIO {
        char &ref;
    };

    struct RatLSPIO {
        std::pair<long long, unsigned long long> &ref;
    };
    struct StringIO {
        std::string &ref;
    };

    struct DelStrIO {
        std::string exp;
    };

    class iofmtguard {
    public:
        iofmtguard(std::basic_ios<char> &s);

        ~iofmtguard();

    private:
        std::basic_ios<char> &s_;
        char fill_;
        std::streamsize precision_;
        std::basic_ios<char>::fmtflags fmt_;
    };
}
#endif //T2_DATASTRUCT_H
