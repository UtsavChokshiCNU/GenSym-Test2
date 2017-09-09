
#include "stdafx.h"
#include "TestJServerMessages.h"
#include "JChartXML.h"
#include "JString.h"


CPPUNIT_TEST_SUITE_REGISTRATION(TestJServerMessages);


CString getText(xmlNodePtr root, const char* szTag);
void InitDoubleArray(xmlNodePtr pRoot, double*& value, int len);
bool Compare(double* arr1, double* arr2, int len);
LPWSTR GetStr(CString& str);
inline int toInt(const CString& str);
// -------+++++++------- -------+++++++------- //
void TestJServerMessages::Test()
{
	CPPUNIT_ASSERT(TestSetIntXML());
	CPPUNIT_ASSERT(TestSetStringXML());
	CPPUNIT_ASSERT(TestSetDoubleXML());
	CPPUNIT_ASSERT(TestSetDoubleArrayXML());
	CPPUNIT_ASSERT(TestCreateXML());
	CPPUNIT_ASSERT(TestExportAction());

	JChartConnectionTest test1;
	JChartDestroy test2(44);
	JChartPrint test3(55);
	JChartUpdate test4(66);
	JChartCopy test5(77);

	CPPUNIT_ASSERT(TestServerSimpleMessage(test1, -1, _T("Test")));
	CPPUNIT_ASSERT(TestServerSimpleMessage(test2, 44, _T("Destroy")));
	CPPUNIT_ASSERT(TestServerSimpleMessage(test3, 55, _T("Print")));
	CPPUNIT_ASSERT(TestServerSimpleMessage(test4, 66, _T("Update")));
	CPPUNIT_ASSERT(TestServerSimpleMessage(test5, 77, _T("Copy")));
}
// -------+++++++------- -------+++++++------- //
bool TestJServerMessages::TestSetIntXML() const
{
	long handle = 1, prop = 2, i = 3, j = 4, value = 6;
	long _handle = 0, _prop = 0, _i = 0, _j = 0, _value = 0;
	JChartSetInt jMess(handle, prop, i, j, value);
	JString szMessage = jMess;
	xmlDocPtr pDoc = xmlParseMemory(szMessage, strlen(szMessage));

	if ( pDoc != NULL )
	{
		xmlNodePtr pRoot = xmlDocGetRootElement(pDoc);
		if ( pRoot != NULL )
		{
			_handle = toInt(getText(pRoot, JServerMessage::m_szHandleTag));
			_prop = toInt(getText(pRoot, JChartSet::m_szPropTag));
			_i = toInt(getText(pRoot, JChartSet::m_szITag));
			_j = toInt(getText(pRoot, JChartSet::m_szJTag));
			_value = toInt(getText(pRoot, JChartSet::m_szValueTag));
		}
		xmlFreeDoc(pDoc);
	}

	return (handle == _handle) && (prop == _prop) && (i == _i) && (j == _j) && (value == _value);
}
// -------+++++++------- -------+++++++------- //
bool TestJServerMessages::TestSetStringXML() const
{

	long handle = 4, prop = 5, i = 23, j = 4;
	CString value = _T(" TESTTTTT & STRINgggggg !!!!!!!"), _value = _T("");
	long _handle = 0, _prop = 0, _i = 0, _j = 0;
	JChartSetString jMess(handle, prop, i, j, GetStr(value));
	JString szMessage = jMess;
	xmlDocPtr pDoc = xmlParseMemory(szMessage, strlen(szMessage));

	if ( pDoc != NULL )
	{
		xmlNodePtr pRoot = xmlDocGetRootElement(pDoc);
		if ( pRoot != NULL )
		{
			_handle = toInt(getText(pRoot, JServerMessage::m_szHandleTag));
			_prop = toInt(getText(pRoot, JChartSet::m_szPropTag));
			_i = toInt(getText(pRoot, JChartSet::m_szITag));
			_j = toInt(getText(pRoot, JChartSet::m_szJTag));
			_value = getText(pRoot, JChartSet::m_szValueTag);
		}
		xmlFreeDoc(pDoc);
	}
	return (handle == _handle) && (prop == _prop) && (i == _i) && (j == _j) && (value == _value);
}
// -------+++++++------- -------+++++++------- //
bool TestJServerMessages::TestSetDoubleXML() const
{
	long handle = 111, prop = 2332, i = 23, j = 233334;
	long _handle = 0, _prop = 0, _i = 0, _j = 0;
	double value = 1.2345, _value = 0;
	JChartSetDouble jMess(handle, prop, i, j, value);
	JString szMessage = jMess;
	xmlDocPtr pDoc = xmlParseMemory(szMessage, strlen(szMessage));

	if ( pDoc != NULL )
	{
		xmlNodePtr pRoot = xmlDocGetRootElement(pDoc);
		if ( pRoot != NULL )
		{
			_handle = toInt(getText(pRoot, JServerMessage::m_szHandleTag));
			_prop = toInt(getText(pRoot, JChartSet::m_szPropTag));
			_i = toInt(getText(pRoot, JChartSet::m_szITag));
			_j = toInt(getText(pRoot, JChartSet::m_szJTag));
			_value = wcstod(getText(pRoot, JChartSet::m_szValueTag), NULL);
		}
		xmlFreeDoc(pDoc);
	}
	return (handle == _handle) && (prop == _prop) && (i == _i) && (j == _j) && (value == _value);
}
// -------+++++++------- -------+++++++------- //
bool TestJServerMessages::TestSetDoubleArrayXML() const
{
	long handle = 111, prop = 2332, i = 3, j = 3;
	long _handle = 0, _prop = 0, _i = 0, _j = 0;
	double value[] = {1.011111, 2.1, 34.11111};
	double* _value = NULL;
	bool flag = false;
	JChartSetDoubleArray jMess(handle, prop, i, j, value);
	JString szMessage = jMess;
	xmlDocPtr pDoc = xmlParseMemory(szMessage, strlen(szMessage));

	if ( pDoc != NULL )
	{
		xmlNodePtr pRoot = xmlDocGetRootElement(pDoc);
		if ( pRoot != NULL )
		{
			_handle = toInt(getText(pRoot, JServerMessage::m_szHandleTag));
			_prop = toInt(getText(pRoot, JChartSet::m_szPropTag));
			_i = toInt(getText(pRoot, JChartSet::m_szITag));
			_j = toInt(getText(pRoot, JChartSet::m_szJTag));
			InitDoubleArray(pRoot, _value, j);
			flag = Compare(value, _value, j);
			delete [] _value;
		}
		xmlFreeDoc(pDoc);
	}
	return (handle == _handle) && (prop == _prop) && (i == _i) && (j == _j) && flag;
}
// -------+++++++------- -------+++++++------- //
bool TestJServerMessages::TestCreateXML() const
{

	long handle = 23444, chart_type = 32234, x = 34, y = 34, width = 100, height = 200;
	long _handle = 0, _chart_type = 0, _x = 0, _y = 0, _width = 0, _height = 0;
	CString title = _T("testtttttttttt      CHARTTTT"), _title = _T("");
	JChartCreate jMess(handle, chart_type, GetStr(title), x, y, width, height);
	JString szMessage = jMess;
	xmlDocPtr pDoc = xmlParseMemory(szMessage, strlen(szMessage));

	if ( pDoc != NULL )
	{
		xmlNodePtr pRoot = xmlDocGetRootElement(pDoc);
		if ( pRoot != NULL )
		{
			_handle = toInt(getText(pRoot, JServerMessage::m_szHandleTag));
			_chart_type = toInt(getText(pRoot, JChartCreate::m_szTypeTag));
			_x = toInt(getText(pRoot, JChartCreate::m_szXCoordTag));
			_y = toInt(getText(pRoot, JChartCreate::m_szYCoordTag));
			_width = toInt(getText(pRoot, JChartCreate::m_szWidthTag));
			_height = toInt(getText(pRoot, JChartCreate::m_szHeightTag));
			_title = getText(pRoot, JChartCreate::m_szTitleTag);
		}
		xmlFreeDoc(pDoc);
	}

	return (handle == _handle) && (chart_type == _chart_type) && (x == _x) &&
		(y == _y) && (width == _width) && (height == _height) && (title == _title);
}
// -------+++++++------- -------+++++++------- //
bool TestJServerMessages::TestServerSimpleMessage(JServerMessage& message, long handle, CString action) const
{
	long _handle = 0;
	CString _action = _T("");
	JString szMessage = message;
	xmlDocPtr pDoc = xmlParseMemory(szMessage, strlen(szMessage));

	if ( pDoc != NULL )
	{
		xmlNodePtr pRoot = xmlDocGetRootElement(pDoc);
		if ( pRoot != NULL )
		{
			_handle = toInt(getText(pRoot, JServerMessage::m_szHandleTag));
			_action = getText(pRoot, JChartCreate::m_szActionTag);
		}
		xmlFreeDoc(pDoc);
	}

	return (handle == _handle) && (action == _action);
}
// -------+++++++------- -------+++++++------- //
bool TestJServerMessages::TestExportAction() const
{
	const long handle = 23, width = 444, height = 666, format = 3;
	long _handle = 0, _width = 0, _height = 0, _format = 0;
	const CString action = _T("Export");
	CString pathname = _T("Path path pathhhhhh");
	CString _action = _T(""), _pathname = _T("");
	JChartExport jMess(handle, width, height, format, GetStr(pathname));
	JString szMessage = jMess;
	xmlDocPtr pDoc = xmlParseMemory(szMessage, strlen(szMessage));

	if ( pDoc != NULL )
	{
		xmlNodePtr pRoot = xmlDocGetRootElement(pDoc);
		if ( pRoot != NULL )
		{
			_handle = toInt(getText(pRoot, JServerMessage::m_szHandleTag));
			_action = getText(pRoot, JServerMessage::m_szActionTag);
			_width = toInt(getText(pRoot, JChartExport::m_szWidthTag));
			_height = toInt(getText(pRoot, JChartExport::m_szHeightTag));
			_format = toInt(getText(pRoot, JChartExport::m_szFormatTag));
			_pathname = getText(pRoot, JChartExport::m_szPathnameTag);
		}
		xmlFreeDoc(pDoc);
	}

	return (handle == _handle) && (action == _action) && (width == _width) 
		&& (height == _height) && (format == _format) && (pathname == _pathname);
}
// -------+++++++------- -------+++++++------- //
// -------+++++++------- -------+++++++------- //
CString getText(xmlNodePtr root, const char* szTag)
{
	xmlNodePtr element = NULL;
	for (xmlNodePtr node = root->children; node; node = node->next)
	{
		if ( 0 == strcmp(szTag, (const char*)node->name) )
		{
			return CString(node->last->content);
		}
	}
	return _T("");
}
// -------+++++++------- -------+++++++------- //
void InitDoubleArray(xmlNodePtr pRoot, double*& value, int len)
{
	int i =0;
	value = new double[len];
	xmlNodePtr element = NULL;

	for (xmlNodePtr node = pRoot->children; node; node = node->next)
	{
		if ( 0 == strcmp(JChartSet::m_szValueTag, (const char*)node->name) )
		{
			for (xmlNodePtr node1 = node->children; node1; node1 = node1->next)
			{
				if ( 0 == strcmp(JChartSetDoubleArray::m_szItemTag, (const char*)node1->name) )
				{
					CString str(node1->last->content);
					value[i++] = wcstod(str, NULL);
					if (len == i)
					{
						return;
					}
				}
			}
			return;
		}
	}
	
}
// -------+++++++------- -------+++++++------- //
bool Compare(double* arr1, double* arr2, int len)
{
	for(int i = 0; i < len; i++)
	{
		if (arr1[i] != arr2[i])
		{
			return false;
		}
	}
	return true;
}
// -------+++++++------- -------+++++++------- //
LPWSTR GetStr(CString& str)
{
	int len = str.GetLength();
	LPWSTR val = LPWSTR( str.GetBuffer(len) );
	str.ReleaseBuffer();
	return val;
}
// -------+++++++------- -------+++++++------- //
inline int toInt(const CString& str)
{
	int result = -1;
	if (!str.IsEmpty())
	{
		result = _ttoi(str);
	}

	return result;
}
