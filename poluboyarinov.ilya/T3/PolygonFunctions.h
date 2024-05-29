#ifndef POLYGON_FUNCTIONS_H
#define POLYGON_FUNCTIONS_H
#include <functional>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <cmath>
#include "Polygon.h"
namespace nspace
{
	void area(std::vector<Polygon>& vector);
	void max(std::vector<Polygon>& vector);
	void min(std::vector<Polygon>& vector);
	void count(std::vector<Polygon>& vector);
	void rmecho(std::vector<Polygon>& vector);
	void same(std::vector<Polygon>& vector);
}
#endif
