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
	//tm tt = *localtime(&t);
	tm tt;
	localtime_s(&tt,&t);

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
/*
 * 将MFC的CString类型转为string类型 
 * 
 * param
 *		cstr
 *
 * return
 *		返回转换后的string类型
 *
*/
stringT Convert::StringConvert::cstring2string(const CString & cstr)
{
	stringT str;
	//str = (char*)cstring2char(cstr);
	return str;
}
CString Convert::StringConvert::string2cstring(const std::string str)
{
	CString ret = _T("");
	ret = str.c_str();
	return ret;
}
#endif
std::string Convert::StringConvert::dword2string(const DWORD& value)
{
	std::string ret = "";
	char szHex[10] = {0};
	char pch[] = "0123456789ABCDEF";
	szHex[0] = '0';
	szHex[1] = 'x';

	for (int i = 0; i < 8; i++) {
		szHex[2 + i] = *(pch + (((value) >> (28 - i * 4)) & 0xF));
	}
	ret = szHex;

	return ret;
}
DWORD Convert::StringConvert::hexstring2dword(const std::string val)
{
	char szHex[10];
	for (unsigned int i = 0; i<val.length(); i++)
		szHex[i] = val[i];
	szHex[val.length()] = '\0';

	DWORD dwValue = 0;
	if (strstr(szHex, "0x")) {
		strcpy_s(szHex, szHex + 2);
		szHex[8] = '\0';
	}
	_strupr_s(szHex);
	char chrTmp[] = "0123456789ABCDEF";
	char *pFind = NULL;
	for (int i = 0; i < 8; i++) {
		pFind = strchr(chrTmp, szHex[i]);
		dwValue = dwValue | (((DWORD)(pFind - chrTmp) << (7 - i) * 4) & 0xFFFFFFFF);
	}
	return dwValue;
}
std::string Convert::StringConvert::tchar2string(TCHAR * pTChar)
{
	int nLen = WideCharToMultiByte(CP_ACP, 0, pTChar, -1, NULL, 0, NULL, NULL);

	char* chRtn = new char[nLen * sizeof(char)];

	WideCharToMultiByte(CP_ACP, 0, pTChar, -1, chRtn, nLen, NULL, NULL);

	std::string str(chRtn);

	return str;
}

char * Convert::StringConvert::cstring2char(CString cstr)
{
	int len = cstr.GetLength();
	char* chRtn = (char*)malloc((len * 2 + 1) * sizeof(char));//CString的长度中汉字算一个长度   
	memset(chRtn, 0, 2 * len + 1);
	USES_CONVERSION;
	strcpy_s(chRtn, 2 * len + 1, OLE2A(cstr.LockBuffer()));
	return (LPSTR)chRtn;
}

