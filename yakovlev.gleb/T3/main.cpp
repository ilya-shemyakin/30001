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

    while (!std::cin.eof()) {
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        std::cin >> cmd;
        isError = true;

        if (std::cin.eof()) {
            break;
        }

        else if (cmd == "COUNT") {
            if (count(polygons) >= 0) {
                std::cout << count(polygons) << '\n';
                isError = false;
            }
        }
        else if (cmd == "MAX") {
            if (max(polygons) >= 0) {
                std::cout << max(polygons) << '\n';
                isError = false;
            }
        }
        else if (cmd == "MIN") {
            if (min(polygons) >= 0) {
                std::cout << min(polygons) << '\n';
                isError = false;
            }
        }
        else if (cmd == "AREA") {
            if (area(polygons) >= 0) {
                std::cout << area(polygons) << '\n';
                isError = false;
            }
        }
        else if (cmd == "RECTS") {
            std::cout << rects(polygons) << '\n';
        }
        else if (cmd == "MAXSEQ") {
            if (maxSeq(polygons) >= 0) {
                std::cout << maxSeq(polygons) << '\n';
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
