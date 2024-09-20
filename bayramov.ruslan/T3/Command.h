#ifndef COMMAND_H
#define COMMAND_H

#include "Polygon.h"

using std::string;
using std::vector;
using std::ostream;
using std::istream;

using namespace nspace;

ostream& area(istream& in, ostream& out, vector<Polygon>& polygons);
ostream& max(istream& in, ostream& out, vector<Polygon>& polygons);
ostream& min(istream& in, ostream& out, vector<Polygon>& polygons);
ostream& count(istream& in, ostream& out, vector<Polygon>& polygons);
ostream& lessarea(istream& in, ostream& out, vector<Polygon>& polygons);
ostream& same(istream& in, ostream& out, vector<Polygon>& polygons);

double getArea(Polygon& polygon);
#endif
