#include "commandFunctions.h"


bool sameCorners(Polygon& pol, int a) {
    return (pol.points.size() == a);
}

bool isEvenCountOfCorners(Polygon& pol) {
    return !(pol.points.size() % 2);
}

double findAreaOfPolygon(Polygon& pol) {
    auto GaussianLacing = [] (double sum, const Point& point, const Point& nextPoint) {
        return sum + point.x * nextPoint.y - nextPoint.x * point.y;
    };

    double area = std::accumulate(pol.points.begin(), pol.points.end() - 1, 0.0, 
        [&GaussianLacing](double sum, const Point& point) {
            return GaussianLacing(sum, point, *(std::next(&point)));
    });

    area += (pol.points[pol.points.size() - 1].x * pol.points[0].y - 
        pol.points[pol.points.size() - 1].y * pol.points[0].x);

    return std::fabs((area) / 2);
}

void area(std::vector<Polygon>& polygons) {
    Iofmtguard iofmtguard(std::cout);

    std::string temp;
    std::cin >> temp;
    std::cout << std::fixed << std::setprecision(1);
    if (temp == "ODD") {
        std::cout << std::accumulate(polygons.begin(), polygons.end(), 0.0, [] (double area, Polygon& pol)
            {
            area += (!isEvenCountOfCorners(pol) ? findAreaOfPolygon(pol) : 0);
            return area;
            }) << '\n';
    }
    else if (temp == "MEAN") {
        std::cout << std::accumulate(polygons.begin(), polygons.end(), 0.0, [] (double area, Polygon& pol)
            {
            area += findAreaOfPolygon(pol);
            return area; 
            }) / polygons.size() << '\n';
    }
    else if (temp == "EVEN") {
        std::cout << std::accumulate(polygons.begin(), polygons.end(), 0.0, [] (double area, Polygon& pol)
            {
            area += (isEvenCountOfCorners(pol) ? findAreaOfPolygon(pol) : 0);
            return area; 
            }) << '\n';
    }
    else {
        std::istringstream iss(temp);
        int i = 0;
        if (iss >> i && iss.eof() && i >= 3) {
            std::cout << std::accumulate(polygons.begin(), polygons.end(), 0.0, [i] (double area, Polygon& pol)
                {
                area += (sameCorners(pol, i) ? findAreaOfPolygon(pol) : 0);
                return area; 
                }) << '\n';
        }
        else {
            std::cout << "<INVALID COMMAND>\n";
        }
    }
}


void count(std::vector<Polygon>& polygons) {
    std::string temp;
    std::cin >> temp;
    if (temp == "ODD") {
        std::cout << std::count_if(polygons.begin(), polygons.end(), std::bind(std::logical_not<bool>(), std::bind(isEvenCountOfCorners, _1))) << '\n';
    }
    else if (temp == "EVEN") {
        std::cout << std::count_if(polygons.begin(), polygons.end(), std::bind(isEvenCountOfCorners, _1)) << '\n';
    }
    else {
        std::istringstream iss(temp);
        int i = 0;
        if (iss >> i && iss.eof() && i >= 3) {
            std::cout << std::count_if(polygons.begin(), polygons.end(), std::bind(sameCorners, _1, i)) << '\n';
        }
        else {
            std::cout << "<INVALID COMMAND>\n";
        }
    }
}

void max(std::vector<Polygon>& polygons) {
    Iofmtguard iofmtguard(std::cout);

    std::string temp;
    std::cin >> temp;
    if (temp == "VERTEXES") {
        auto maxItem = std::max_element(polygons.begin(), polygons.end(), std::bind([&] (Polygon& pol1, Polygon& pol2)
        { 
            return pol1.points.size() < pol2.points.size(); 
        }, _1, _2));

        double res = (*maxItem).points.size();
        std::cout << res << '\n';
    }
    else if (temp == "AREA") {
        std::cout << std::fixed << std::setprecision(1);
        auto maxItem = std::max_element(polygons.begin(), polygons.end(), std::bind([&] (Polygon& pol1, Polygon& pol2)
        { 
            return findAreaOfPolygon(pol1) < findAreaOfPolygon(pol2); 
        }, _1, _2));

        double res = findAreaOfPolygon(*maxItem);
        std::cout << res << '\n';
    }
    else {
        std::cout << "<INVALID COMMAND>\n";
    }
}

void min(std::vector<Polygon>& polygons) {
    Iofmtguard iofmtguard(std::cout);
    std::string temp;
    std::cin >> temp;
    if (temp == "VERTEXES") {
        auto minItem = std::min_element(polygons.begin(), polygons.end(), std::bind([&] (Polygon& pol1, Polygon& pol2)
        { 
            return pol1.points.size() < pol2.points.size(); 
        }, _1, _2));

        double res = (*minItem).points.size();
        std::cout << res << '\n';
    }
    else if (temp == "AREA") {
        std::cout << std::fixed << std::setprecision(1);
        auto minItem = std::min_element(polygons.begin(), polygons.end(), std::bind([&] (Polygon& pol1, Polygon& pol2)
        { 
            return findAreaOfPolygon(pol1) < findAreaOfPolygon(pol2); 
        }, _1, _2));

        double res = findAreaOfPolygon(*minItem);
        std::cout << res << '\n';
    }
    else {
        std::cout << "<INVALID COMMAND>\n";
    }    
}

bool isRectangle(Polygon& pol) {
    auto getDistance = [&pol] (const Point& a, const Point& b)
        {
            return (std::sqrt(std::pow(a.x - b.x, 2.0) + std::pow(a.y - b.y, 2.0)));
        };
    bool isRect = false;
    if (pol.points.size() == 4) {
        if (getDistance(pol.points[0], pol.points[2]) == getDistance(pol.points[1], pol.points[3])) {
            isRect = true;
        }
    }
    return isRect;
}

void rects(std::vector<Polygon>& polygons) {
    std::cout << std::count_if(polygons.begin(), polygons.end(), isRectangle) << '\n';
}

void maxSeq(std::vector<Polygon>& polygons) {
    Polygon polygon;

    std::string temp = "";
    std::getline(std::cin >> std::noskipws, temp, '\n');
    std::istringstream iss(temp);

    if (!(iss >> polygon)) {
        std::cout << "<INVALID COMMAND>\n";
        return;
    }

    bool isSeries = false;
    int counter = 0;

    std::vector<int> generatedVector;
    std::transform(polygons.begin(), polygons.end(), std::back_inserter(generatedVector), [&isSeries, &counter, &polygon] (Polygon& pol) mutable { 
        if (pol == polygon) {
            ++counter;
            isSeries = true;
        } 
        else{
            counter = 0;
            isSeries = false;
        }
        return counter; 
    });

    generatedVector.push_back(0);
    std::cout << *std::max_element(generatedVector.begin(), generatedVector.end()) << '\n';
}