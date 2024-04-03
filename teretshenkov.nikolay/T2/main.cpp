#include "DataStruct.h"

int main()
{
    std::vector<DataStruct> dataVector;
    while (std::cin.good())  //завершается после ввода ^Z
    {
        std::copy(
            std::istream_iterator<DataStruct>(std::cin),  
            std::istream_iterator<DataStruct>(),
            std::back_inserter(dataVector)
        );
        if (std::cin.fail() && !std::cin.eof())
        {
            std::cin.clear();
            std::cin.ignore();
        }
    }

    std::sort(dataVector.begin(), dataVector.end(), sortData);
    for (const DataStruct& data : dataVector)
    {
        std::cout << data << std::endl;
    }
    return 0;
}
