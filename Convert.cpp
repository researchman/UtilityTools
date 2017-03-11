#include "stdafx.h"
#include "Convert.h"

time_t Convert::TimeConvert::systemtime2time_t(const SYSTEMTIME & st)
{
	struct tm gm = { st.wSecond, st.wMinute, st.wHour + 8, st.wDay, st.wMonth - 1, st.wYear - 1900, st.wDayOfWeek, 0, 0 };
	return mktime(&gm);
}

SYSTEMTIME Convert::TimeConvert::time_t2systemtime(const time_t& t)
{
	//tm tt = *localtime(&t);
	tm tt;
	localtime_s(&tt, &t);

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

std::string Convert::TimeConvert::time_t2string(const time_t& t)
{
	std::string ret = "";
	struct tm *p = new tm;
	char buf[30] = { 0 };

	int nError = localtime_s(p,&t);

	if (nError == 0) {
		sprintf_s(buf,
			30,
			"%04d-%02d-%02d %02d:%02d:%02d",
			p->tm_year + 1900, p->tm_mon + 1, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec);
	}	
	ret = buf;

	delete p;
	p = NULL;

	return ret;
}

std::string Convert::TimeConvert::systemtime2string(const SYSTEMTIME & st)
{
	char buf[30] = { 0 };
	sprintf_s(buf,
		30,
		"%u-%u-%u %u:%u:%u.%u",
		st.wYear, st.wMonth, st.wDay,
		st.wHour + 8, st.wMinute, st.wSecond, st.wMilliseconds);

	std::string ret = "";
	ret = buf;

	return ret;
}
