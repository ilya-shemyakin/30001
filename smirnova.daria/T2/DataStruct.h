#ifndef TP_LABA1_DATASTRUCT_H
#define TP_LABA1_DATASTRUCT_H
#include <iostream>
namespace nspace {
    struct DataStruct {
        unsigned long long key1;
        unsigned long long key2;
        std::string key3;
    };

    struct DelimiterIO {
        char exp;
    };

    struct UllLitIO {
        unsigned long long &ref;
    };

    struct UllHexIO {
        unsigned long long &ref;
    };

    struct StringIO {
        std::string &ref;
    };

    struct LabelIO {
        std::string exp;
    };

    // scope guard для возврата состояния потока в первоначальное состояние
    class iofmtguard {
    public:
        iofmtguard(std::basic_ios<char> &s) noexcept;

        ~iofmtguard();

    private:
        std::basic_ios<char> &s_;
        char fill_;
        std::streamsize precision_;
        std::basic_ios<char>::fmtflags fmt_;
    };

    std::istream &operator>>(std::istream &in, DelimiterIO &&dest);

    std::istream &operator>>(std::istream &in, StringIO &&dest);

    std::istream &operator>>(std::istream &in, UllLitIO &&dest);

    std::istream &operator>>(std::istream &in, UllHexIO &&dest);

    std::istream &operator>>(std::istream &in, LabelIO &&dest);

    std::istream &operator>>(std::istream &in, DataStruct &dest);

    std::ostream &operator<<(std::ostream &out, const DataStruct &dest);

    bool sortFunction(const DataStruct &firstElement, const DataStruct &secondElement);
}
#endif
