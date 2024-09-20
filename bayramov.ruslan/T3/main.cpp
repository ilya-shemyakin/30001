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
    if (arg < 2) // ������ �������� - ��� ����� ���������, ������� ������� "< 2", � �� "< 1"
    {
        return 1;
    }
    std::ifstream input(file[1]);
    if (!input)
    {
        return 1; // ��� �������� 1 ��������� �� ������
    }
    using namespace nspace;
    setlocale(LC_ALL, "rus");
    vector<Polygon> polygons;
    std::map<std::string, std::function<void(std::istream&, std::ostream&, vector<Polygon>&)>> command;
    command["AREA"] = area;
    command["MAX"] = max; // �������� ��������� std::map ��� �������� ��������� � ��������
    command["MIN"] = min;
    command["COUNT"] = count;
    command["LESSAREA"] = lessarea;
    command["SAME"] = same;
    cout.setstate(std::ios_base::failbit); // ����� � ����� ������ ������� �� ��������
    while (!input.eof())
    {
        std::copy(
            std::istream_iterator< Polygon >(input),
            std::istream_iterator< Polygon >(),
            std::back_inserter(polygons)
        );
        if (input.fail() and !input.eof()) // ���������� ����� �� �����
        {
            input.clear();
            input.ignore();
        }
    }
    cout.clear(); // ��������������� �����, ������ ����� ���������
    std::string cmd;
    while (!cin.eof()) // ���������� ������ �� ������ cin
    {
        try
        {
            cin >> cmd;
            if (cin.eof())
            {
                break;
            }
            auto func = command.find(cmd);
            if (func == command.end()) // ���� ������� �� �������, �� ��������� ������� �� ����� ������ ������������
            {
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw std::invalid_argument("");
            }
            func->second(cin, cout, polygons); // ��������� � �������� �����
        }
        catch (...)
        {
            cout << "<INVALID COMMAND>" << endl;
        }
        if (cin.fail())
        {
            cin.clear();
            cout << "<INVALID COMMAND>" << endl;// ����������� � ���������� ������. ������ ��� ����� ������, ������ ���.
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}
