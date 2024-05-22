#ifndef T3_COMMANDOFFIGURE_H
#define T3_COMMANDOFFIGURE_H
#include <functional>
#include <map>
#include <ostream>
#include <string>
#include "Polygon.h"
double sumOfArea(double sum, const Polygon& polygon);
double getPolygonAreas(const Point &p1, const Point &p2);
double getArea(const Polygon& polygon);
void getAreaOfFigure(const std::string& commands,  std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons);
void evenAreaOfFigure(const std::vector< Polygon >& polygons, std::ostream& output);
void meanAreaOfFigure(const std::vector< Polygon >& polygons, std::ostream& output);
bool countFunctor(const Polygon& polygon, std::size_t size);
size_t numOfVertexes(const std::string& command, const std::vector< Polygon >& polygons);
bool isEvenOddCountFunctor(const Polygon& polygon);
void minArea(const std::vector< Polygon >& polygons, std::ostream& output);
void maxArea(const std::vector< Polygon >& polygons, std::ostream& output);
void maxVertexes(const std::vector< Polygon >& polygons, std::ostream& output);
void minVertexes(const std::vector< Polygon >& polygons, std::ostream& output);
void area(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
void max(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
void min(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
void vertexCount(size_t num, const std::vector< Polygon >& polygons, std::ostream& output);
void countEven(const std::vector< Polygon >& polygons, std::ostream& output);
void countOdd(const std::vector< Polygon >& polygons, std::ostream& output);
void count(const std::vector< Polygon >& polygons, std::istream& input, std::ostream& output);
void intersections(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
void rmecho(std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
void warning(std::ostream& output, const std::string& mes);
#endif
