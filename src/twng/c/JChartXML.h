#pragma once

#include <libxml\parser.h>
#include "JString.h"

// -------+++++++------- JServerMessage class -------+++++++------- //
class JServerMessage
{

public:
	static const char* m_szHandleTag;
	static const char* m_szMainTag;
	static const char* m_szActionTag;

public:
	operator JString() const;
	JServerMessage(long handle, const char* szAction);
	~JServerMessage();

protected:
	xmlNodePtr JServerMessage::SetElement(const char* szTagName, const char* szValue, xmlNodePtr pRoot = NULL);

protected:
	long m_handle;
	xmlDocPtr m_pDoc;
	xmlNodePtr m_pRoot;
};

// -------+++++++------- JChartSet class -------+++++++------- //
class JChartSet: public JServerMessage
{
public:
	static const char* m_szPropTag;
	static const char* m_szITag;
	static const char* m_szJTag;
	static const char* m_szValueTag;

protected:
	JChartSet(long handle, const char* szAction, long prop, long i, long j);
	
	template<class T>
	xmlNodePtr SetSimpleValue(T value)
	{
		JString szValue(value);
		return SetElement(m_szValueTag, szValue);		
	}

protected:
	long m_nProp;
	long m_nI;
	long m_nJ;
};

// -------+++++++------- JChartSetInt class -------+++++++------- //
class JChartSetInt: public JChartSet
{
public:
	JChartSetInt(long handle, long prop, long i, long j, long value);

public:
	static const char* m_szSetIntAction;

protected:
	long m_nValue;
};

// -------+++++++------- JChartSetString class -------+++++++------- //
class JChartSetString: public JChartSet
{
public:
	JChartSetString(long handle, long prop, long i, long j, LPWSTR value);

public:
	static const char* m_szSetStringAction;

protected:
	LPWSTR m_szValue;
};

// -------+++++++------- JChartSetDouble class -------+++++++------- //
class JChartSetDouble: public JChartSet
{
public:
	JChartSetDouble(long handle, long prop, long i, long j, double value);

public:
	static const char* m_szSetDoubleAction;

protected:
	double m_dValue;
};

// -------+++++++------- JChartSetDoubleArray class -------+++++++------- //
class JChartSetDoubleArray: public JChartSet
{
public:
	JChartSetDoubleArray(long handle, long prop, long i, long j, double* value);

public:
	static const char* m_szSetDoubleArrayAction;
	static const char* m_szItemTag;

protected:
	double* m_dArray;
};

// -------+++++++------- JChartCreate class -------+++++++------- //
class JChartCreate: public JServerMessage
{
public:
	JChartCreate(long handle, long chart_type, LPWSTR title, long x, long y, long width, long height);

public:
	static const char* m_szTypeTag;
	static const char* m_szTitleTag;
	static const char* m_szXCoordTag;
	static const char* m_szYCoordTag;
	static const char* m_szWidthTag;
	static const char* m_szHeightTag;
	static const char* m_szJChartCreateAction;

protected:
	long m_nType;
	LPWSTR m_szTitle;
	long m_nX;
	long m_nY;
	long m_nWidth;
	long m_nHeight;
};

// -------+++++++------- JChartCreate class -------+++++++------- //
class JChartConnectionTest: public JServerMessage
{
public:
	JChartConnectionTest();

public:
	static const char* m_szTestAction;
};

// -------+++++++------- JChartDestroy class -------+++++++------- //
class JChartDestroy: public JServerMessage
{
public:
	JChartDestroy(long handle);

public:
	static const char* m_szDestroy;
};

// -------+++++++------- JChartPrint class -------+++++++------- //
class JChartPrint: public JServerMessage
{
public:
	JChartPrint(long handle);

public:
	static const char* m_szPrint;
};

// -------+++++++------- JChartUpdate class -------+++++++------- //
class JChartUpdate: public JServerMessage
{
public:
	JChartUpdate(long handle);

public:
	static const char* m_szUpdate;
};

// -------+++++++------- JChartExport class -------+++++++------- //
class JChartExport: public JServerMessage
{
public:
	JChartExport(long handle, long width, long height, long format, LPWSTR pathname);

public:
	static const char* m_szExport;
	static const char* m_szFormatTag;
	static const char* m_szPathnameTag;
	static const char* m_szWidthTag;
	static const char* m_szHeightTag;

protected:
	long m_nWidth;
	long m_nHeight; 
	long m_nFormat;
	LPWSTR m_szPathname;
};

// -------+++++++------- JChartCopy class -------+++++++------- //
class JChartCopy: public JServerMessage
{
public:
	JChartCopy(long handle);

public:
	static const char* m_szCopy;
};
