#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iterator>
struct DataStruct
{
    unsigned long long key1;
    unsigned long long key2;
    std::string key3;
};
std::istream& operator>>(std::istream& ss, DataStruct& data) {
    char temp;
    ss >> temp >> temp;
    std::string key;
    std::string value;
    for (int i = 0; i < 3; i++)
    {
        std::getline(ss,key,' ');
        std::getline(ss,value,':');
        std::stringstream valueTemp(value);
        if (key == "key3")
        {
            valueTemp >> data.key3;
        }
        else if(key == "key2")
        {

            valueTemp >> std::oct >> data.key2;
        }
        else if(key == "key1")
        {
            valueTemp >> data.key1;
        }
    }
    ss>>temp;
    return ss;
}
std::ostream & operator<<(std::ostream &stream,
                          const DataStruct &data) {
    return stream << "(:key1 " << data.key1 << "ULL:key2 " << std::oct << std::showbase
    << data.key2 << ":key3 "  << data.key3 << ":)\n" << std::dec << std::noshowbase;

}
bool compareDataStruct(const DataStruct &a, const DataStruct &b) {
    if (a.key1 != b.key1)
        return a.key1 < b.key1;
    if (a.key2 != b.key2)
        return a.key2 < b.key2;
    return a.key3.size() < b.key3.size();
}
int main()
{
    std::vector<DataStruct> data;
    std::string input;
    getline (std::cin, input);
    std::istringstream iss(input);
    std::istream_iterator<DataStruct> begin(iss);
    std::istream_iterator<DataStruct> end;
    std::copy(begin, end, std::back_inserter(data));
    std::sort(data.begin(), data.end(), compareDataStruct);
    for (const DataStruct &ds : data) {
        std::cout << ds;
    }
}
