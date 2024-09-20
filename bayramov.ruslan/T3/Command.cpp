#include "Command.h"
#include "Iofmtquard.h"


using std::cout;
using std::endl;


double getArea(Polygon& polygon) // ���������� ������� �� ������� ������
{
    double area = 0;
    int number = polygon.points.size();
    if (number > 0)
    {
        for (int i = 0; i < number; ++i)
        {
            int j = (i + 1) % number;
            area += (polygon.points[i].x * polygon.points[j].y - polygon.points[j].x * polygon.points[i].y);
        }
        area = std::abs(area) / 2;
        return area;
    }
    return 0;
}
// � ������� ������� ��� � ������� std::accumulate � ������-���������, �� �� ����������. ���� � ���, ��� �� ������ ��������
// ���������� ������ �����, �.�. Point. ������ � �� ���� ������ ���������� �� �������.
ostream& area(istream& in, ostream& out, vector<Polygon>& polygons)
{
    string str;
    in >> str;
    Iofmtguard fmtguard(out); // ���������� ��������� ������
    out << std::fixed << std::setprecision(1); // �������� 1 ���� ����� �������
    if (str == "EVEN")
    {
        return out << std::accumulate(polygons.begin(), polygons.end(), 0.0,
            [](double sum, Polygon& p) // ������� ����� ������ ��������� polygons � �������� ���������, ��������� std::accumulate ������� ������ ���
            {
                return sum + (p.points.size() % 2 == 0 ? getArea(p) : 0);
            }) << endl;
    }
    else if (str == "ODD")
    {
        return out << std::accumulate(polygons.begin(), polygons.end(), 0.0,
            [](double sum, Polygon& p)
            {
                return sum + (p.points.size() % 2 != 0 ? getArea(p) : 0);
            }) << endl;
    }
    else if (str == "MEAN")
    {
        if (polygons.empty())
        {
            throw std::invalid_argument("������������ ����������");
        }
        return out << std::accumulate(polygons.begin(), polygons.end(), 0.0,
            [](double sum, Polygon& p)
            {
                return sum + getArea(p);
            }) / polygons.size() << endl;
    }
    else
    {
        size_t numberOfVertexes = 0;
        try
        {
            numberOfVertexes = std::stoi(str);
            if (numberOfVertexes > 2)
            {
                return out << std::accumulate(polygons.begin(), polygons.end(), 0.0,
                    [numberOfVertexes](double sum, Polygon& p)
                    {
                        return sum + (p.points.size() == numberOfVertexes ? getArea(p) : 0);
                    }) << endl;
            }
            else
            {
                throw std::invalid_argument("������������ ��������");
            }
        }
        catch (...)
        {
            throw std::invalid_argument("������������ ��������");
        }
    }
}



ostream& max(istream& in, ostream& out, vector<Polygon>& polygons)
{
    string str;
    in >> str;
    Iofmtguard fmtguard(out);
    out << std::fixed << std::setprecision(1);
    if (polygons.size() != 0)
    {
        if (str == "AREA") // std::max_element ���������� ��������, ������� ����� �������� * ����� ���, ����� ������������ � ����� ��������
        {
            double area = getArea(*std::max_element(polygons.begin(), polygons.end(), [](Polygon& p1, Polygon& p2)
                {
                    return (getArea(p1) < getArea(p2));
                }));
            return out << area << endl;
        }
        else if (str == "VERTEXES")
        {
            return out << (*std::max_element(polygons.begin(), polygons.end(), [](Polygon& p1, Polygon& p2)
                {
                    return (p1.points.size() < p2.points.size());
                })).points.size() << endl;
        }
        else
        {
            throw std::invalid_argument("������������ ��������");
        }
    }
    else
    {
        return out << "<INVALID COMMAND>" << endl;
    }
}
ostream& min(istream& in, ostream& out, vector<Polygon>& polygons)
{
    string str;
    in >> str;
    Iofmtguard fmtguard(out);
    out << std::fixed << std::setprecision(1);
    if (polygons.size() != 0)
    {
        if (str == "AREA")
        {
            return out << getArea(*std::min_element(polygons.begin(), polygons.end(), [](Polygon& p1, Polygon& p2)
                {
                    return (getArea(p1) < getArea(p2));
                })) << endl;
        }
        else if (str == "VERTEXES")
        {
            return out << (*std::min_element(polygons.begin(), polygons.end(), [](Polygon& p1, Polygon& p2)
                {
                    return (p1.points.size() < p2.points.size());
                })).points.size() << endl;
        }
        else
        {
            throw std::invalid_argument("������������ ��������");
        }
    }
    else
    {
        return out << "<INVALID COMMAND>" << endl;
    }
}



ostream& count(istream& in, ostream& out, vector<Polygon>& polygons)
{
    string str;
    in >> str;
    Iofmtguard fmtguard(out);
    if (str == "EVEN")
    {
        return out << std::count_if(polygons.begin(), polygons.end(), [](Polygon& p)
            {
                return (p.points.size() % 2 == 0);
            }) << endl;
    }
    else if (str == "ODD")
    {
        return out << std::count_if(polygons.begin(), polygons.end(), [](Polygon& p)
            {
                return (p.points.size() % 2 != 0);
            }) << endl;
    }
    else
    {
        size_t numberOfVertexes = 0;
        try
        {
            numberOfVertexes = std::stoi(str);
            if (numberOfVertexes > 2)
            {
                return out << std::count_if(polygons.begin(), polygons.end(), [numberOfVertexes](Polygon& p)
                    {
                        return (p.points.size() == numberOfVertexes);
                    }) << endl;
            }
            else
            {
                throw std::invalid_argument("������������ ��������");
            }
        }
        catch (...)
        {
            throw std::invalid_argument("������������ ��������");
        }
    }
}



ostream& lessarea(istream& in, ostream& out, vector<Polygon>& polygons)
{
    Polygon temp;
    in >> temp;
    string str = "";
    std::getline(in, str);
    if (in.fail())
    {
        return out;
    }
    else if (str != "")
    {
        return out << "<INVALID COMMAND>" << endl;
    }
    Iofmtguard fmtguard(out);
    double area = getArea(temp);
    return out << std::count_if(polygons.begin(), polygons.end(), [area](Polygon& p)
        {
            return (getArea(p) < area);
        }) << endl;
}



void sortPoints(Polygon& polygon)
{
    std::sort(polygon.points.begin(), polygon.points.end(), [](Point& point1, Point& point2)
        {
            return (point1.x == point2.x) ? point1.y < point2.y : point1.x < point2.x;
        });
} // ���������� ������� �� �, ����� �� �. ��� ��������� ��������� ����� � ������������ ������� � �������.



bool isSame(Polygon polygon1, Polygon polygon2)
{
    size_t size = polygon1.points.size();
    if (size == polygon2.points.size())
    {
        sortPoints(polygon1);
        sortPoints(polygon2);
        int diffX = polygon2.points[0].x - polygon1.points[0].x;
        int diffY = polygon2.points[0].y - polygon1.points[0].y;
        std::transform(polygon2.points.begin(), polygon2.points.end(), polygon2.points.begin(), [diffX, diffY](Point& point)
            {
                point.x -= diffX; // ��������� ������ �� ������ �����
                point.y -= diffY;
                return point;
            });
        return (polygon1 == polygon2);
    }
    else
    {
        return false;
    }
}



ostream& same(istream& in, ostream& out, vector<Polygon>& polygons)
{
    Polygon temp;
    in >> temp;
    string str = "";
    std::getline(in, str);
    if (in.fail())
    {
        return out;
    }
    else if (str != "")
    {
        return out << "<INVALID COMMAND>" << endl;
    }
    Iofmtguard fmtguard(out);
    return out << std::count_if(polygons.begin(), polygons.end(), [temp](Polygon& p)
        {
            return (isSame(temp, p));
        }) << endl;
}
