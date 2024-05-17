#ifndef T3_COMMANDOFFIGURE_H
#define T3_COMMANDOFFIGURE_H
#include <functional>
#include <map>
#include <ostream>
#include <string>
#include "Polygon.h"
char ERROR_IN_COMMAND[] = "INVALID COMMAND";
struct PolygonArea {
    Point p1;
    double operator()(double area, const Point& p2);
};

void getAreaOfFigure(const std::string& command, std::ostream& out, const std::vector< Polygon >& polygons);
bool countFunctor(const Polygon& polygon, std::size_t size);
size_t numOfVertexes(const std::string& command, const std::vector< Polygon >& polygons);
bool isEvenOddCountFunctor(const Polygon& polygon);
void getMinArea(const std::vector< Polygon >& polygons, std::ostream& out);
void getMaxArea(const std::vector< Polygon >& polygons, std::ostream& out);
void getMinVertex(const std::vector< Polygon >& polygons, std::ostream& out);
void getMaxVertex(const std::vector< Polygon >& polygons, std::ostream& out);

void area(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
void max(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
void min(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
void count(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
void intersections(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
void rmecho(std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
#endif
