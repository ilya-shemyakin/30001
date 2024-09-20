#ifndef COMMAND_FUNCTIONS_H
#define COMMAND_FUNCTIONS_H

#include "Polygon.h"
#include "Iofmtguard.h"

using namespace std::placeholders;

bool sameCorners(Polygon& pol, int a);
bool isEvenCountOfCorners(Polygon& pol);
double findAreaOfPolygon(Polygon& pol);
bool isRectangle(Polygon& pol);

int count(std::vector<Polygon>& polygons);
double area(std::vector<Polygon>& polygons);
double max(std::vector<Polygon>& polygons);
double min(std::vector<Polygon>& polygons);

int rects(std::vector<Polygon>& polygons);
int maxSeq(std::vector<Polygon>& polygons);

#endif
