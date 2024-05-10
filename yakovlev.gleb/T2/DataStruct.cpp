#include "DataStruct.h"

std::istream& operator>>(std::istream& in, DelimiterIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) {
        return in;
    }
    char c = '0';
    in >> c;

    if (in && (std::toupper(c) != std::toupper(dest.exp))) {
        in.setstate(std::ios::failbit);
    }
    return in;
}

std::istream& operator>>(std::istream& in, DblSciIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) {
        return in;
    }
    dest.ref = 0;
    std::string temp = "";
    std::getline(in, temp, ':');
    std::istringstream iss(temp);

    bool findE = (temp.find('E') != std::string::npos || temp.find('e') != std::string::npos);
    if (findE && iss >> dest.ref) {
    }
    else {
        in.setstate(std::ios::failbit);
    }

    return in;
}

std::istream& operator>>(std::istream& in, StringIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) {
        return in;
    }
    return std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"');
}

std::istream& operator>>(std::istream& in, LabelIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) {
        return in;
    }
    for (int i = 0; dest.exp[i] != '\0'; i++) {
        in >> DelimiterIO({ dest.exp[i] });
    }
    
    if (!in) {
        in.setstate(std::ios::failbit);
    }

    return in;
}

std::istream& operator>>(std::istream& in, UllBinIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) {
        return in;
    }
    std::string temp = "";
    std::getline(in >> LabelIO{ "0b" }, temp, ':');

    bool isCorrect = true;
    dest.ref = 0;
    
    if (temp == "") {
        in.setstate(std::ios::failbit);
        return in;
    }

    for (int i = temp.length() - 1; (i >= 0 && isCorrect); i--) {
        switch (temp[i]) {
            case '0':
                break;
            case '1':
                dest.ref += std::pow(2.0, temp.length()- 1 - i);
                break;
            default:
                in.setstate(std::ios::failbit);
                isCorrect = false;
                break;
        }
    }
    return in;
}

std::istream& operator>>(std::istream& in, DataStruct& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) {
        return in;
    }
    Iofmtguard fmtguard(in);

    DataStruct input;
    {
        using sep = DelimiterIO;
        using label = LabelIO;
        using dbl = DblSciIO;
        using str = StringIO;
        using integ = UllBinIO;

        in >> sep{ '(' } >> sep{ ':' };
        for (int i = 0; (i < 3) && in; i++) {
            in >> label{ "key" };
            char temp = '\0';
            in >> temp;
            switch (temp) {
                case '1':
                    in >> std::scientific >> dbl{ input.key1 };
                    break;
                case '2':
                    in >> integ{ input.key2 };
                    break;
                case '3':
                    in >> str{ input.key3 } >> sep{ ':' };
                    break;
                default:
                    in.setstate(std::ios::failbit);
                    break;
            }
        }
        in >> sep{ ')' };
    }
    if (in) {
        dest = input;
    }
    return in;
}

std::string showExpForm(double number) {
    std::stringstream ss;
    ss << std::setprecision(2) << std::scientific << number;
    std::string str = "";
    ss >> str;
    bool extraZeros = true;
    std::string temp = "";
    for (size_t i = str.find('e') + 2; i < str.length() && extraZeros; i++) {
        if (str[i] != '0') {
            temp = str.substr(i);
            extraZeros = false;
        }
    }

    return str.substr(0, str.find('e')+2) + temp;
}

std::string transformIntToBin(int number) {
    std::string temp = (number == 0) ? "0" : "";
    while (number > 0) {
        temp = ((number % 2) ? "1" : "0") + temp;
        number /= 2;
    }

    return ("0b" + temp);
}

std::ostream& operator<<(std::ostream& out, const DataStruct& src) {
    std::ostream::sentry sentry(out);
    if (!sentry) {
        return out;
    }
    Iofmtguard fmtguard(out);
    out << "(:";
    out << "key1 " << showExpForm(src.key1) << ":";
    out << "key2 " << transformIntToBin(src.key2) << ":";
    out << "key3 " << '"' << src.key3 << "\":)";
    return out;
}
