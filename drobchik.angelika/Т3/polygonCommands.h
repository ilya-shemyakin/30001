#ifndef _COMMANDS_H
#define _COMMANDS_H

#include <functional>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <cmath>
#include "Polygon.h"

void lessarea(std::vector< Polygon >& polygon, Polygon dest, std::ostream& out);
void maxseq(std::vector< Polygon >& polygons, Polygon dest, std::ostream& out);

void area(std::vector< Polygon >& polygons, std::string& mode, std::ostream& out);
void max(std::vector< Polygon >& polygons, std::string& mode, std::ostream& out);
void min(std::vector< Polygon >& polygons, std::string& mode, std::ostream& out);
void count(std::vector< Polygon >& polygons, std::string& mode, std::ostream& out);

#endif
