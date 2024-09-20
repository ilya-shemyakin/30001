#include <fstream>
#include "polygonCommands.h"

int main(int nArguments, char** file)
{
    if (nArguments < 2) {
        return 1;
    }

    std::ifstream inputF(file[1]);
    if (!inputF) {
        return 1;
    }

    std::vector< Polygon > polygon;
    while (!inputF.eof()) {
        std::copy(
            std::istream_iterator<Polygon>(inputF),
            std::istream_iterator<Polygon>(),
            std::back_inserter(polygon)
        );
        if (inputF.fail() && !inputF.eof()) {
            inputF.clear();
            inputF.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    std::cin.clear();

    while (!std::cin.eof()) {
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        try {
            std::string command;
            std::string mode;
            std::map <std::string, int> cases;
            cases["AREA"] = 1;
            cases["MAX"] = 2;
            cases["MIN"] = 3;
            cases["COUNT"] = 4;
            cases["LESSAREA"] = 5;
            cases["MAXSEQ"] = 6;

            std::cin >> command;
            if (std::cin.eof()) {
                break;
            }
            switch (cases[command]) {
            case 1:
                std::cin >> mode;
                area(polygon, mode, std::cout);
                break;
            case 2:
                std::cin >> mode;
                max(polygon, mode, std::cout);
                break;
            case 3:
                std::cin >> mode;
                min(polygon, mode, std::cout);
                break;
            case 4:
                std::cin >> mode;
                count(polygon, mode, std::cout);
                break;
            case 5:
                lessarea(polygon, std::cin, std::cout);
                break;
            case 6:
                maxseq(polygon, std::cin, std::cout);
                break;
            default:
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw std::invalid_argument("");
            }
        }
        catch (std::invalid_argument& e) {
            std::cout << "<INVALID COMMAND>" << std::endl;
            std::cin.clear();
        }
    }

    return 0;
}
