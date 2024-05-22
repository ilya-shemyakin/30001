#ifndef T3_COMMANDOFFIGURE_H
#define T3_COMMANDOFFIGURE_H
#include <functional>
#include <map>
#include <ostream>
#include <string>
#include "Polygon.h"
double sumOfArea(double sum, const Polygon& polygon);
double getArea(const Polygon& polygon);
void getAreaOfFigure(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons);
void evenAreaOfFigure(const std::vector< Polygon >& polygons, std::ostream& output);
void meanAreaOfFigure(const std::vector< Polygon >& polygons, std::ostream& output);
double calculatePolygonAreaRec(const Polygon& polygon, size_t i, double area);
void cmdCount(const std::vector< Polygon >& polygons, std::istream& input, std::ostream& output);
void vertexArea(size_t num, const std::vector< Polygon >& polygons, std::ostream& output);
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
