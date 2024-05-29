#ifndef COMMAND_FUNCTIONS_H
#define COMMAND_FUNCTIONS_H

#include "Polygon.h"
#include "Iofmtguard.h"

using namespace std::placeholders;

bool sameCorners(Polygon& pol, int a);
bool isEvenCountOfCorners(Polygon& pol);
double findAreaOfPolygon(Polygon& pol);
bool isRectangle(Polygon& pol);

void count(std::vector<Polygon>& polygons);
void area(std::vector<Polygon>& polygons);
void max(std::vector<Polygon>& polygons);
void min(std::vector<Polygon>& polygons);

void rects(std::vector<Polygon>& polygons);
void maxSeq(std::vector<Polygon>& polygons);


#endif