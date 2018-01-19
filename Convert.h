#ifndef UTILITY_TOOLS_CONVERT_H
#define UTILITY_TOOLS_CONVERT_H
#include <string>
#include <time.h>
#include <vector>
#include <algorithm>
#include <Windows.h>
#include <atlstr.h>

using namespace std;

#ifdef UNICODE
typedef std::wstring stringT;
#else
typedef std::string stringT;
#endif

namespace Convert {
	namespace TimeConvert {
		time_t systemtime2time_t(const SYSTEMTIME& st);
		SYSTEMTIME time_t2systemtime(const time_t& t);

		std::string time_t2string(const time_t& t);
		std::string systemtime2string(const SYSTEMTIME& st);
	}
	namespace StringConvert {
#ifdef _WIN32
		stringT cstring2string(const CString& cstr);
		CString string2cstring(const std::string str);
#else
		

#endif
		std::string dword2string(const DWORD& value);
		DWORD hexstring2dword(const std::string val);

		std::string tchar2string(TCHAR* pTChar);
		char* cstring2char(CString cstr);

		std::vector<std::string> split(const std::string& value,const std::string& delim,bool ignored);
	}
}

#endif // !UTILITY_TOOLS_CONVERT_H
