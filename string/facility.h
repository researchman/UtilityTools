#ifndef STRING_FACILITY_H
#define STRING_FACILITY_H

#include <vector>
#include <string>
#include <algorithm>
#include <map>

#include "meta/point.h"

using namespace std;

namespace utility {
	class string_facility {
	public:
		string_facility() {}
		~string_facility() {}
	public:
		static vector<string> Split(const string& source, const string& delim, bool ignored);
	};

	class file_facility {
	public:
		file_facility() {}
		~file_facility() {}
	public:
		static std::map<int, point::YPoint<double>> LoadData();
	};

	class geometry_facility {
	public:
		geometry_facility() {}
		~geometry_facility() {}
	public:
		static point::YPoint<double> Circle(point::YPoint<double>& p1, point::YPoint<double>& p2, point::YPoint<double>& p3, double& radius);
		static bool IsOnStraightLine(point::YPoint<double>& p1, point::YPoint<double>& p2, point::YPoint<double>& p3);
	};
};

#endif