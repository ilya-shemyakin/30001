#include <fstream>
#include <map>
#include "iostream"
#include "Command.h"
using std::vector;
using std::cout;
using std::cin;
using std::endl;
int main(int arg, char** file)
{
    if (arg < 2) // Первый аргумент - имя самой программы, поэтому пишется "< 2", а не "< 1"
    {
        return 1;
    }
    std::ifstream input(file[1]);
    if (!input)
    {
        return 1; // Код возврата 1 указывает на ошибку
    }
    using namespace nspace;
    setlocale(LC_ALL, "rus");
    vector<Polygon> polygons;
    std::map<std::string, std::function<void(std::istream&, std::ostream&, vector<Polygon>&)>> command;
    command["AREA"] = area;
    command["MAX"] = max; // Создание структуры std::map для удобного обращения к командам
    command["MIN"] = min;
    command["COUNT"] = count;
    command["LESSAREA"] = lessarea;
    command["SAME"] = same;
    while (!input.eof())
    {
        std::copy(
            std::istream_iterator< Polygon >(input),
            std::istream_iterator< Polygon >(),
            std::back_inserter(polygons)
        );
        if (input.fail() and !input.eof()) // Считывание фигур из файла
        {
            input.clear();
            input.ignore();
        }
    }
    std::string cmd;
    while (!cin.eof()) // Считывание команд из потока cin
    {
        if (cin.fail())
        {
            cin.clear();
        }
        try
        {
            cin >> cmd;
            if (cin.eof())
            {
                break;
            }
            auto func = command.find(cmd);
            if (func == command.end()) // Если команда не найдена, то следующие символы до конца строки пропускаются
            {
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw std::invalid_argument("");
            }
            func->second(cin, cout, polygons); // Обращение к значению ключа
        }
        catch (...)
        {
            cout << "<INVALID COMMAND>" << '\n';
        }
    }
}
//
