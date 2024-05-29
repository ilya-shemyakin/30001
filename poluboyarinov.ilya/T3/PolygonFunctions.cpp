#include "PolygonFunctions.h"
#include "Polygon.h"

#include <cmath>

namespace nspace
{
	void nspace::area(std::vector<Polygon>& vector)
	{
		std::string command = "";
		std::cin >> command;
		if (command == "ODD")
		{
			double result = std::accumulate(vector.begin(), vector.end(), 0.0,
				[](double res, Polygon figure) {
				if (figure.points.size() % 2 == 0)
				{
					res += figure.getArea();
					return res;
				}
				else
				{
					res += 0;
					return res;
				}});
			std::cout << std::fixed << std::setprecision(1);
			std::cout << result << std::endl;
		}
		else if (command == "EVEN")
		{
			double result = std::accumulate(vector.begin(), vector.end(), 0.0,
				[](double res, Polygon figure) {
				if (figure.points.size() % 2 == 1)
				{
					res += figure.getArea();
					return res;
				}
				else
				{
					res += 0;
					return res;
				}});
			std::cout << std::fixed << std::setprecision(1);
			std::cout << result << std::endl;
		}
		else if (command == "MEAN")
		{
			if (vector.size() > 0)
			{
				double result = std::accumulate(vector.begin(), vector.end(), 0.0,
					[](double res, Polygon figure) {
					res += figure.getArea();
					return res;
					});
				std::cout << std::fixed << std::setprecision(1);
				std::cout << result / vector.size() << std::endl;
			}
			else
			{
				throw std::invalid_argument("ERROR");
			}
		}
		else if (std::accumulate(command.begin(), command.end(), true, [](bool acc, char c) {
			return acc && std::isdigit(c);
			}))
		{
			int number = std::stoi(command);
			double result = std::accumulate(vector.begin(), vector.end(), 0.0,
				[number](double res, Polygon figure) {
				if (figure.points.size() == number)
				{
					res += figure.getArea();
					return res;
				}
				else
				{
					res += 0;
					return res;
				}});
			std::cout << std::fixed << std::setprecision(1);
			std::cout << result << std::endl;
		}
		else
		{
			throw std::invalid_argument("ERROR");
		}
	}

	void max(std::vector<Polygon>& vector)
	{
		std::string command = "";
		std::cin >> command;
		if (command == "AREA")
		{
			double result = std::accumulate(vector.begin(), vector.end(), 0.0,
				[](double res, Polygon figure) {
				res = std::max(res, figure.getArea());
				return res; });
			std::cout << std::fixed << std::setprecision(1);
			std::cout << result << std::endl;
		}
		else if (command == "VERTEXES")
		{
			double result = std::accumulate(vector.begin(), vector.end(), 0.0,
				[](size_t res, Polygon figure) {
				res = std::max(res,	figure.points.size());
				return res; });
			std::cout << result << std::endl;
		}
		else
		{
			throw std::invalid_argument("ERROR");
		}
	}

	void min(std::vector<Polygon>& vector)
	{
		std::string command = "";
		std::cin >> command;
		if (command == "AREA")
		{
			double result = std::accumulate(vector.begin(), vector.end(), std::numeric_limits<double>::max(),
				[](double res, Polygon figure) {
				res = std::min(res, figure.getArea());
				return res; });
			std::cout << std::fixed << std::setprecision(1);
			std::cout << result << std::endl;
		}
		else if (command == "VERTEXES")
		{
			size_t result = std::accumulate(vector.begin(), vector.end(), std::numeric_limits<size_t>::max(),
				[](size_t res, Polygon figure) {
				res = std::min(res, figure.points.size());
				return res; });
			std::cout << result << std::endl;
		}
		else
		{
			throw std::invalid_argument("ERROR");
		}
	}

	void count(std::vector<Polygon>& vector)
	{
		std::string command = "";
		std::cin >> command;
		if (command == "ODD")
		{
			int result = std::accumulate(vector.begin(), vector.end(), 0,
				[](int res, Polygon figure) {
					if (figure.points.size() % 2 == 0)
					{
						res += 1;
						return res;
					}
					else
					{
						res += 0;
						return res;
					}});
			std::cout << result << std::endl;
		}
		else if (command == "EVEN")
		{
			int result = std::accumulate(vector.begin(), vector.end(), 0,
				[](int res, Polygon figure) {
					if (figure.points.size() % 2 == 1)
					{
						res += 1;
						return res;
					}
					else
					{
						res += 0;
						return res;
					}});
			std::cout << result << std::endl;
		}
		else if (std::accumulate(command.begin(), command.end(), true, [](bool acc, char c) {
			return acc && std::isdigit(c);
			}))
		{
			int number = std::stoi(command);
			int result = std::accumulate(vector.begin(), vector.end(), 0.0,
				[number](double res, Polygon figure) {
					if (figure.points.size() == number)
					{
						res += 1;
						return res;
					}
					else
					{
						res += 0;
						return res;
					}});
			std::cout << result << std::endl;
		}
		else
		{
			throw std::invalid_argument("ERROR");
		}
	}

	void rmecho(std::vector<Polygon>& vector)
	{
		Polygon polygon;
		std::cin >> polygon;
		/*if (vector.empty() or !std::cin || std::cin.peek() != '\n')
		{
			std::cin.setstate(std::ios::failbit);
		}*/
		auto isSimilar = [&polygon](Polygon& first, Polygon& second) {
			return  first == polygon && second == polygon; };
		auto toRemoveIt = std::unique(vector.begin(), vector.end(), isSimilar);
		std::size_t removedCount = std::distance(toRemoveIt, vector.end());
		vector.erase(toRemoveIt, vector.end());
		std::cout << removedCount;
	}


	bool isSame(const Polygon& first, const Polygon& second)
	{
		using namespace std::placeholders;
		if (first.points.size() != second.points.size()) {
			return false;
		}
		std::vector< Point > firstCopy;
		firstCopy.reserve(first.points.size());
		std::vector< Point > secondCopy;
		secondCopy.reserve(first.points.size());
		std::vector< bool > areTranslatedPoints;

		std::copy(std::begin(first.points), std::end(first.points), std::back_inserter(firstCopy));
		std::copy(std::begin(second.points), std::end(second.points), std::back_inserter(secondCopy));

		std::sort(firstCopy.begin(), firstCopy.end(), [](Point& p1, Point& p2) {
			if (p1.x == p2.x) {
				return p1.y < p2.y;
			}
			return p1.x < p2.x;
			});
		std::sort(secondCopy.begin(), secondCopy.end(), [](Point& p1, Point& p2) {
			if (p1.x == p2.x) {
				return p1.y < p2.y;
			}
			return p1.x < p2.x;
			});
		int diffX = firstCopy[0].x - secondCopy[0].x;
		int diffY = firstCopy[0].y - secondCopy[0].y;

		std::transform(secondCopy.begin(), secondCopy.end(), secondCopy.begin(), [diffX, diffY](Point& point)
			{
				point.x += diffX;
				point.y += diffY;
				return point;
			});

		bool result = true;
		for (int i = 0; i < firstCopy.size(); i++)
		{
			if (firstCopy[i].x != secondCopy[i].x || firstCopy[i].y != secondCopy[i].y)
			{
				result = false;
			}
		}
		return result;
	}

	void same(std::vector<Polygon>& vector)
	{
		Polygon polygon;
		std::cin >> polygon;

		using namespace std::placeholders;
		auto isSameAsFig = std::bind(isSame, _1, polygon);

		std::cout << std::count_if(vector.begin(), vector.end(), isSameAsFig) << std::endl;
	}
}
