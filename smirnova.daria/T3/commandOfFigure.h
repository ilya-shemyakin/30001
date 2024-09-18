#ifndef T3_COMMANDOFFIGURE_H
#define T3_COMMANDOFFIGURE_H
#include <functional>
#include <map>
#include <ostream>
#include <string>
#include "Polygon.h"
void areaOfFigure(const std::vector< Polygon >& polygons, std::istream& input, std::ostream& output);
void evenArea(const std::vector< Polygon >& polygons, std::ostream& output);
void oddArea(const std::vector< Polygon >& polygons, std::ostream& output);
void meanArea(const std::vector< Polygon >& polygons, std::ostream& output);
void vertexArea(size_t num, const std::vector< Polygon >& polygons, std::ostream& output);
double plusArea(double sum, const Polygon& polygon);
double gaussFormula(const Point& p1, const Point& p2);
double calculatePolygonArea(const Polygon& polygon);
double calculatePolygonAreaRec(const Polygon& polygon, size_t i, double area);

void maxOfFigure(const std::vector< Polygon >& polygons, std::istream& input, std::ostream& output);
void findMaxArea(const std::vector< Polygon >& polygons, std::ostream& output);
void findMaxVertexes(const std::vector< Polygon >& polygons, std::ostream& output);

void minOfFigure(const std::vector< Polygon >& polygons, std::istream& input, std::ostream& output);
void findMinArea(const std::vector< Polygon >& polygons, std::ostream& output);
void findMinVertexes(const std::vector< Polygon >& polygons, std::ostream& output);

void countOfFigure(const std::vector< Polygon >& polygons, std::istream& input, std::ostream& output);
void countEven(const std::vector< Polygon >& polygons, std::ostream& output);
void countOdd(const std::vector< Polygon >& polygons, std::ostream& output);
void vertexCount(size_t num, const std::vector< Polygon >& polygons, std::ostream& output);
void intersections(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
void rmecho(std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
#endif
