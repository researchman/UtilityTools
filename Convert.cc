#include "stdafx.h"
#include "Convert.h"

/*
 * 时间转换函数：将SYSTEMTIME转为time_t结构
 *
 * param
 *		st
 *
 * return
 *		转换后的time_t结构值
 *
*/
time_t Convert::TimeConvert::systemtime2time_t(const SYSTEMTIME & st)
{
	struct tm gm = { st.wSecond, st.wMinute, st.wHour + 8, st.wDay, st.wMonth - 1, st.wYear - 1900, st.wDayOfWeek, 0, 0 };
	return mktime(&gm);
}

/*
* 时间转换函数：将time_t转为SYSTEMTIME结构
*
* param
*		t
*
* return
*		转换后的SYSTEMTIME结构值
*
*/
SYSTEMTIME Convert::TimeConvert::time_t2systemtime(const time_t& t)
{
	tm tt = *localtime(&t);

	SYSTEMTIME st = { 1900 + tt.tm_year,
		1 + tt.tm_mon,
		tt.tm_wday,
		tt.tm_mday,
		tt.tm_hour,
		tt.tm_min,
		tt.tm_sec,
		0 };

	return st;
}

/*
* 时间转换函数：将time_t转为string类型
*
* param
*		t
*
* return
*		转换后的string字符串
*
*/
std::string Convert::TimeConvert::time_t2string(const time_t& t)
{
	std::string ret = "";
	struct tm *p = NULL;
	p = new tm;
	char buf[30] = { 0 };

	int nError = localtime_s(p,&t);

	if (nError == 0) {
		sprintf_s(buf,
			30,
			"%04d-%02d-%02d %02d:%02d:%02d",
			p->tm_year + 1900, p->tm_mon + 1, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec);
	}	
	ret = buf;

	if (p) {
		delete p;
		p = NULL;
	}

	return ret;
}

/*
* 时间转换函数：将SYSTEMTIME转为string类型
*
* param
*		st
*
* return
*		转换后的string字符串
*
*/
std::string Convert::TimeConvert::systemtime2string(const SYSTEMTIME & st)
{
	std::string ret = "";
	char buf[30] = { 0 };
	sprintf_s(buf,
		30,
		"%u-%u-%u %u:%u:%u.%u",
		st.wYear, st.wMonth, st.wDay,
		st.wHour + 8, st.wMinute, st.wSecond, st.wMilliseconds);
	ret = buf;

	return ret;
}

#ifdef _WIN32
std::string Convert::StringConvert::cstring2string(const CString & cstr)
{
#ifdef UNICODE
	std::wstring str;
#else
	std::string str;
#endif
	str = cstr.GetBuffer(0);
	return str;
}
#endif
