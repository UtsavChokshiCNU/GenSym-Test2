#include "stdafx.h"
#include "JString.h"

JString::JString(long nNumber)
{
	CString str;
	str.Format(_T("%d"), nNumber);
	Convert(str);
}

JString::JString(const char* szStr)
{
	CopyStr(szStr);
}

JString::JString(double dNumber)
{
	CString str;
	str.Format(_T("%f"), dNumber);
	Convert(str);
}

JString::JString(const CString& szStr)
{
	Convert(szStr);
}

JString::JString(LPWSTR pStr)
{
	CString szConvert(pStr);
	Convert(szConvert);
}

JString::JString(const JString& szStr)
{
	if (m_pStr != szStr.m_pStr )
	{
		CopyStr(szStr.m_pStr);
	}
}

JString::~JString()
{
	delete []m_pStr;
	m_pStr = NULL;

}

JString::operator const char*() const
{
	return m_pStr;
}

void JString::Convert(const CString& szStr)
{
	USES_CONVERSION;
	CopyStr(T2A(szStr));
}

void JString::CopyStr(const char* str)
{
	int nLength = strlen(str);
	m_pStr = new char[nLength+1];
	strcpy(m_pStr, str);
}
