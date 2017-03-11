#ifndef UTILITY_TOOLS_CONVERT_H
#define UTILITY_TOOLS_CONVERT_H
#include <string>
#include <time.h>

using namespace std;

namespace Convert {
	namespace TimeConvert {
		time_t systemtime2time_t(const SYSTEMTIME& st);
		SYSTEMTIME time_t2systemtime(const time_t& t);

		std::string time_t2string(const time_t& t);
		std::string systemtime2string(const SYSTEMTIME& st);
	}
	namespace StringConvert {
#ifdef _WIN32
		std::string cstring2string(const CString& cstr);
		CString string2cstring(std::string str);
#else

#endif
	}
}

#endif // !UTILITY_TOOLS_CONVERT_H
