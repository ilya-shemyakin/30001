#include "Polygon.h"
#include <sstream>

using std::istream;
using std::string;
using std::vector;
using std::cout;
using std::endl;


namespace nspace
{
    istream& operator>>(istream& in, DelimiterIO&& dest)
    {
        istream::sentry sentry(in);
        if (!sentry) // Получение состояния потока и его проверка
        {
            return in;
        }
        char c = '0';
        in >> c;
        if (in and c != dest.exp)
        { // Если символ не соответствует необходимому, то выставляется флаг ошибки чтения
            in.setstate(std::ios::failbit);
        }
        return in;
    }
    istream& operator>>(istream& in, Point& dest)
    {
        istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        in >> DelimiterIO{ '(' } >> dest.x >> DelimiterIO{ ';' } >> dest.y >> DelimiterIO{ ')' };
        return in; // Проверяется формат
    }
    istream& operator>>(istream& in, Polygon& dest)
    {
        istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        dest.points.clear(); // Очищается вектор
        int size = 0;
        in >> size;
        if (size > 2) // Если размер меньше 2, то задать фигуру нельзя
        {
            char ch;
            vector <Point> temp{};
            int i = 0;
            while (i < size)
            {
                in.get(ch); // Используем get, чтобы не пропустить пробелы
                if (ch == ' ')
                {
                    Point point;
                    in >> point;
                    if (in.fail())
                    {
                        in.clear();
                        in.ignore();
                        break;
                    }
                    if (std::find(temp.begin(), temp.end(), point) == temp.end()) // Условие есть ли точка уже в векторе
                    {
                        temp.push_back(point);
                    }
                }
                else if (ch == '\n')
                {
                    in.clear();
                    cout << "<INVALID COMMAND>" << endl;
                    break;
                }
                else
                {
                    in.setstate(std::ios::failbit);
                    break;
                }
                ++i;
            }
            if (i != size)
            {
                in.setstate(std::ios::failbit);
            }
            if (!in.fail())
            {
                in.get(ch);
                if (ch == '\n')
                {
                    dest.points = temp;
                }
                else
                {
                    in.setstate(std::ios::failbit);
                }
            }
        }
        else
        {
            in.setstate(std::ios::failbit);
        }
        return in;
    }
}
