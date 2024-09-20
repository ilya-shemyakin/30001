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

    std::copy(
        std::begin(polygons),
        std::end(polygons),
        std::ostream_iterator< Polygon >(std::cout, "\n")
    );

    std::string cmd;
    bool isError = true;
    double dTemp = -1.0;
    int iTemp = -1;

    while (!std::cin.eof()) {
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        std::cin >> cmd;
        isError = true;
        dTemp = -1.0;
        iTemp = -1;

        if (std::cin.eof()) {
            break;
        }

        else if (cmd == "COUNT") {
            iTemp = count(polygons);
            if (iTemp >= 0) {
                std::cout << iTemp << '\n';
                isError = false;
            }
        }
        else if (cmd == "MAX") {
            dTemp = max(polygons);
            if (dTemp >= 0) {
                std::cout << dTemp << '\n';
                isError = false;
            }
        }
        else if (cmd == "MIN") {
            dTemp = min(polygons);
            if (dTemp >= 0) {
                std::cout << dTemp << '\n';
                isError = false;
            }
        }
        else if (cmd == "AREA") {
            dTemp = area(polygons);
            if (dTemp >= 0) {
                std::cout << dTemp << '\n';
                isError = false;
            }
        }
        else if (cmd == "RECTS") {
            std::cout << rects(polygons) << '\n';
        }
        else if (cmd == "MAXSEQ") {
            iTemp = maxSeq(polygons);
            if (iTemp >= 0) {
                std::cout << iTemp << '\n';
                isError = false;
            }
        }

        std::cout << std::fixed << std::setprecision(0);
        if (isError) {
            std::cout << "<INVALID COMMAND>\n";
            std::cin.setstate(std::ios::failbit);
        }
    }
    return 0;
}
