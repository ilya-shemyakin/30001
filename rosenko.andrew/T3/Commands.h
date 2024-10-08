#ifndef COMMANDS_H
#define COMMANDS_H

#include <functional>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <string>

#include "Polygon.h"

bool isOdd(const Polygon& polygon);
bool isEven(const Polygon& polygon);
bool isDigit(char ch);
double calcArea(const Polygon& polygon);
double areaIfEven(double area, const Polygon& polygon);
double areaIfOdd(double area, const Polygon& polygon);
double areaIfMean(double area, const Polygon& polygon);

void area(std::vector< Polygon >& polygons, std::istream& input, std::ostream& output);
void max(std::vector< Polygon >& polygons, std::istream& input, std::ostream& output);
void min(std::vector< Polygon >& polygons, std::istream& input, std::ostream& output);
void count(std::vector< Polygon >& polygons, std::istream& input, std::ostream& output);
void rmecho(std::vector< Polygon >& polygons, std::istream& input, std::ostream& output);

int getMaxCoordinate(const Polygon& polygon, int(*getCoordinate)(const Point& point));
int getMinCoordinate(const Polygon& polygon, int(*getCoordinate)(const Point& point));
int getX(const Point& point);
int getY(const Point& point);
std::vector< Point > getFrame(const std::vector< Polygon >& polygons);
bool isInFrame(std::vector< Point >& frame, const Polygon& polygon);

void inframe(std::vector< Polygon >& polygons, std::istream& input, std::ostream& output);

#endif
