#ifndef T3_IOFMTGUARD_H
#define T3_IOFMTGUARD_H
#include <iostream>
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

#endif
