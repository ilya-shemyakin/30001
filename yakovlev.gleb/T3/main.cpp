#include "commandFunctions.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 1;
    }

    std::vector< Polygon > polygons;
    std::ifstream in(argv[1]);

    if (!in.is_open()) {
        return 1;
    }

    for (int i = 0; !in.eof(); i++) {
        std::copy(
            std::istream_iterator< Polygon >(in),
            std::istream_iterator< Polygon >(),
            std::back_inserter(polygons)
        );

        if (!in.eof() && in.fail()) {
            in.clear();
            in.ignore();
        }
    }

    in.close();

    std::string cmd;

    while (!std::cin.eof()) {
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        std::cin >> cmd;
        if (std::cin.eof()) {
            break;
        }
        else if (cmd == "COUNT") {
            count(polygons);
        }
        else if (cmd == "MAX") {
            max(polygons);
        }
        else if (cmd == "MIN") {
            min(polygons);
        }
        else if (cmd == "AREA") {
            area(polygons);
        }
        else if (cmd == "RECTS") {
            rects(polygons);
        }
        else if (cmd == "MAXSEQ") {
            maxSeq(polygons);
        }
        else if (cmd == "MAXSEQ") {
            maxSeq(polygons);
        }
        else {
            std::cout << "<INVALID COMMAND>\n";
            std::cin.setstate(std::ios::failbit);
        }
    }
    return 0;
}
