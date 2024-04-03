#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <string>
#include <complex>

struct DataStruct
{
    unsigned long long key1;
    std::complex<double> key2;
    std::string key3;
};

DataStruct parseDataStruct(const std::string& str)
{
    DataStruct data;
    std::istringstream iss(str);
    std::string token;
    while (iss >> token)
    {
        if (token == ":key1")
        {
            iss >> std::oct >> data.key1;
        }
        else if (token == ":key2")
        {
            double real, imag;
            iss.ignore(); // Ignore '('
            iss >> real >> imag;
            data.key2 = std::complex<double>(real, imag);
        }
        else if (token == ":key3")
        {
            iss.ignore(); // Ignore '\''
            std::getline(iss, data.key3, '\'');
        }
    }
    return data;
}

bool compareDataStruct(const DataStruct& a, const DataStruct& b)
{
    if (a.key1 != b.key1)
    {
        return a.key1 < b.key1;
    }
    else if (std::abs(a.key2) != std::abs(b.key2))
    {
        return std::abs(a.key2) < std::abs(b.key2);
    }
    else
    {
        return a.key3.size() < b.key3.size();
    }
}

int main()
{
    std::vector<DataStruct> dataVector;

    std::string line;
    while (std::getline(std::cin, line))
    {
        try
        {
            DataStruct data = parseDataStruct(line);
            dataVector.push_back(data);
        }
        catch (const std::exception& e)
        {
            continue;
        }
    }

    std::sort(dataVector.begin(), dataVector.end(), compareDataStruct);

    for (const auto& data : dataVector)
    {
        std::cout << "(:key1 " << std::oct << data.key1 <<
            ":key2 #c(" << data.key2.real() << " " << data.key2.imag() <<
            "):key3 '" << data.key3 << "':)" << std::endl;
    }

    return 0;
}
