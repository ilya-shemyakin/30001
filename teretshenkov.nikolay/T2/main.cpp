#include "DataStruct.h"

int main()
{
    std::vector<DataStruct> dataVector;
    while (std::cin.good())  //завершается после ввода ^Z
    {
        std::string sourse;
        std::getline(std::cin, sourse);
        std::istringstream inputStream(sourse);

        std::copy(
            std::istream_iterator<DataStruct>(inputStream),
            std::istream_iterator<DataStruct>(),
            std::back_inserter(dataVector)
        );
    }
    std::sort(dataVector.begin(), dataVector.end(), sortData);
    for (const DataStruct& data : dataVector)
    {
        std::cout << data << std::endl;
    }
    return 0;
}
