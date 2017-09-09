
#include "stdafx.h"
#include "JChartXML.h"
#include "MainFrm.h"

const char* JServerMessage::m_szHandleTag = "handle";
const char* JServerMessage::m_szMainTag = "message";
const char* JServerMessage::m_szActionTag = "action";

const char* JChartSet::m_szPropTag = "property";
const char* JChartSet::m_szITag = "i";
const char* JChartSet::m_szJTag = "j";
const char* JChartSet::m_szValueTag = "value";

const char* JChartSetInt::m_szSetIntAction = "SetInt";

const char* JChartSetString::m_szSetStringAction = "SetString";

const char* JChartSetDouble::m_szSetDoubleAction = "SetDouble";

const char* JChartSetDoubleArray::m_szSetDoubleArrayAction = "SetDoubleArray";
const char* JChartSetDoubleArray::m_szItemTag = "item";

const char* JChartCreate::m_szTypeTag = "type";
const char* JChartCreate::m_szTitleTag = "title";
const char* JChartCreate::m_szXCoordTag = "x";
const char* JChartCreate::m_szYCoordTag = "y";
const char* JChartCreate::m_szWidthTag = "width";
const char* JChartCreate::m_szHeightTag = "height";
const char* JChartCreate::m_szJChartCreateAction = "CreateChart";

const char* JChartConnectionTest::m_szTestAction = "Test";

const char* JChartDestroy::m_szDestroy = "Destroy";
const char* JChartPrint::m_szPrint = "Print";
const char* JChartUpdate::m_szUpdate = "Update";
const char* JChartCopy::m_szCopy = "Copy";

const char* JChartExport::m_szExport = "Export";
const char* JChartExport::m_szFormatTag = "format";
const char* JChartExport::m_szPathnameTag = "pathname";
const char* JChartExport::m_szWidthTag = "width";
const char* JChartExport::m_szHeightTag = "height";



// -------+++++++------- JServerMessage class -------+++++++------- //
JServerMessage::JServerMessage(long handle, const char* szAction)
	: m_handle(handle)
	, m_pDoc(xmlNewDoc(BAD_CAST "1.0"))
	, m_pRoot(xmlNewNode(NULL, BAD_CAST m_szMainTag))
{
	JString szHandle(handle);
	xmlDocSetRootElement(m_pDoc, m_pRoot);
	SetElement(m_szHandleTag, szHandle);
	SetElement(m_szActionTag, szAction);
}

JServerMessage::~JServerMessage()
{
	xmlFreeDoc(m_pDoc);
}

JServerMessage::operator JString() const
{
	xmlChar *pBuff;
	int nSize = 0;
	xmlDocDumpFormatMemory(m_pDoc, &pBuff, &nSize, 1);
	JString szRet((char *)(unsigned char *)pBuff);
	xmlFree(pBuff);
	return szRet;
}

xmlNodePtr JServerMessage::SetElement(const char* szTagName, const char* szValue, xmlNodePtr pRoot)
{
	xmlNodePtr pElem = xmlNewNode(NULL, BAD_CAST szTagName);
	xmlNodeAddContent(pElem, BAD_CAST szValue);
	xmlAddChild(pRoot?pRoot:m_pRoot, pElem);
	return pElem;		
}

// -------+++++++------- JChartSet class -------+++++++------- //
JChartSet::JChartSet(long handle, const char* szAction, long prop, long i, long j)
	: JServerMessage(handle, szAction)
	, m_nProp(prop)
	, m_nI(i)
	, m_nJ(j) 
{
	JString szProp(m_nProp), szI(m_nI), szJ(m_nJ);
	SetElement(m_szPropTag, szProp);
	SetElement(m_szITag, szI);
	SetElement(m_szJTag, szJ);
		
}

// -------+++++++------- JChartSetInt class -------+++++++------- //
JChartSetInt::JChartSetInt(long handle, long prop, long i, long j, long value)
	: JChartSet(handle, m_szSetIntAction, prop, i, j)
	, m_nValue(value) 
{
	SetSimpleValue(m_nValue);
}

// -------+++++++------- JChartSetString class -------+++++++------- //
JChartSetString::JChartSetString(long handle, long prop, long i, long j, LPWSTR value)
	: JChartSet(handle, m_szSetStringAction, prop, i, j)
	, m_szValue(value) 
{
	SetSimpleValue(m_szValue);
}

// -------+++++++------- JChartSetDouble class -------+++++++------- //
JChartSetDouble::JChartSetDouble(long handle, long prop, long i, long j, double value)
	: JChartSet(handle, m_szSetDoubleAction, prop, i, j)
	, m_dValue(value) 
{
	SetSimpleValue(m_dValue);
}

// -------+++++++------- JChartSetDoubleArray class -------+++++++------- //
JChartSetDoubleArray::JChartSetDoubleArray(long handle, long prop, long i, long j, double* value)
	: JChartSet(handle, m_szSetDoubleArrayAction, prop, i, j)
	, m_dArray(value) 
{
	xmlNodePtr pArray = xmlNewNode(NULL, BAD_CAST m_szValueTag);
	for(long p = 0; p < m_nJ; p++) // m_nJ == size of the double array
	{
		JString szDouble(m_dArray[p]);
		SetElement(m_szItemTag, szDouble, pArray);
	}
	xmlAddChild(m_pRoot, pArray);
		
}

// -------+++++++------- JChartCreate class -------+++++++------- //
JChartCreate::JChartCreate(long handle, long chart_type, LPWSTR title, long x, long y, long width, long height)
	: JServerMessage(handle, m_szJChartCreateAction)
	, m_nType(chart_type)
	, m_szTitle(title)
	, m_nX(x)
	, m_nY(y)
	, m_nWidth(width)
	, m_nHeight(height)
{
	JString szType(m_nType), szTitle(m_szTitle), szX(m_nX), 
		szY(m_nY), szWidth(m_nWidth), szHeight(m_nHeight);

	SetElement(m_szTypeTag, szType);
	SetElement(m_szTitleTag, szTitle);
	SetElement(m_szXCoordTag, szX);
	SetElement(m_szYCoordTag, szY);
	SetElement(m_szWidthTag, szWidth);
	SetElement(m_szHeightTag, szHeight);
}

// -------+++++++------- JChartConnectionTest class -------+++++++------- //
JChartConnectionTest::JChartConnectionTest()
	: JServerMessage(-1, m_szTestAction)
{
}

// -------+++++++------- JChartDestroy class -------+++++++------- //
JChartDestroy::JChartDestroy(long handle)
	: JServerMessage(handle, m_szDestroy)
{
}

// -------+++++++------- JChartPrint class -------+++++++------- //
JChartPrint::JChartPrint(long handle)
	: JServerMessage(handle, m_szPrint)
{
}

// -------+++++++------- JChartUpdate class -------+++++++------- //
JChartUpdate::JChartUpdate(long handle)
	: JServerMessage(handle, m_szUpdate)
{
}

// -------+++++++------- JChartExport class -------+++++++------- //
JChartExport::JChartExport(long handle, long width, long height, long format, LPWSTR pathname)
	: JServerMessage(handle, m_szExport)
	, m_nWidth(width)
	, m_nHeight(height)
	, m_nFormat(format)
	, m_szPathname(pathname)
{
	JString szWidth(m_nWidth), szHeight(m_nHeight), 
		szFormat(m_nFormat), szPathname(m_szPathname);

	SetElement(m_szWidthTag, szWidth);
	SetElement(m_szHeightTag, szHeight);
	SetElement(m_szFormatTag, szFormat);
	SetElement(m_szPathnameTag, szPathname);
}

// -------+++++++------- JChartCopy class -------+++++++------- //
JChartCopy::JChartCopy(long handle)
	: JServerMessage(handle, m_szCopy)
{
}
