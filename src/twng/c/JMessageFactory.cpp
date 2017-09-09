#include "stdafx.h"
#include "JMessageFactory.h"
#include "JChartView.h"
#include "JChartServer.h"


const CString JClientMessage::m_szHandleTag = _T("handle");

// -------+++++++------- JMessageFactory class -------+++++++------- //
const CString JMessageFactory::m_szActionTag = _T("action");

JMessageFactory* JMessageFactory::GetInstance()
{
	static JMessageFactory instance;
	return &instance;
}

JMessageFactory::JMessageFactory()
{
	m_Container.Add(Pair(JClientEvent::m_szIdentifier, new JClientEvent()));
	m_Container.Add(Pair(JClientError::m_szIdentifier, new JClientError()));
}

CString getText(xmlNodePtr root, const CString& szTag)
{
	xmlNodePtr element = NULL;
	for (xmlNodePtr node = root->children; node; node = node->next)
	{
		CString tag((const char*)node->name);
		if (tag == szTag)
		{
			return CString(node->last->content);
		}
	}
	return _T("");
}

bool JMessageFactory::ProcessMessage(const CString& szMess)
{
	USES_CONVERSION;
	LPCSTR szMessage = T2A(szMess);

	xmlDocPtr pDoc = xmlParseMemory(szMessage, strlen(szMessage));

	bool isValid = pDoc != NULL;
	if (isValid)
	{
		CString action = getText(xmlDocGetRootElement(pDoc), m_szActionTag);
		JClientMessage* pMessage = Get(T2A(action), xmlDocGetRootElement(pDoc));
		if (pMessage != NULL)
		{
			pMessage->Process();
			delete pMessage;
		}
			
		xmlFreeDoc(pDoc);
	}
	return isValid;
}


JClientMessage* JMessageFactory::Get(LPCSTR szAction, xmlNodePtr pRoot)
{
	JClientMessage* pMess = NULL;
	for(int i =0; i < m_Container.GetSize(); i++)
	{
		if ( m_Container.GetAt(i).m_szKey == szAction )
		{
			pMess = m_Container.GetAt(i).m_pMessage->Clone(pRoot);
			break;
		}
	}
	return pMess;
}

// -------+++++++------- JClientEvent class -------+++++++------- //
const CString JClientEvent::m_szIdentifier = _T("ChartEvent");
const CString JClientEvent::m_szIdTag = _T("id");
const CString JClientEvent::m_szCloseAction = _T("closed");

const CString JClientEvent::m_szSizedAction = _T("resized");
const CString JClientEvent::m_szWidthTag = _T("width");
const CString JClientEvent::m_szHeightTag = _T("height");

const CString JClientEvent::m_szClickedAction = _T("clicked");
const CString JClientEvent::m_szXTag = _T("x");
const CString JClientEvent::m_szYTag = _T("y");
const CString JClientEvent::m_szZTag = _T("z");
const CString JClientEvent::m_szSubsetTag = _T("subset");
const CString JClientEvent::m_szPointTag = _T("point");

inline int toInt(const CString& str)
{
	int result = -1;
	if (!str.IsEmpty())
	{
		result = _ttoi(str);
	}

	return result;
}

inline double toDouble(const CString& str)
{
	double result = -1;
	if (!str.IsEmpty())
	{
		result = _tcstod(str, 0);
	}

	return result;
}

void JClientEvent::Process()
{
	CString szId = getText(m_pRoot, m_szIdTag);
	CString handle = getText(m_pRoot, m_szHandleTag);
	int nHandle = toInt(handle);
	G2JChartView *pCV = JChartServer::GetInstance()->FindChartByHandle(nHandle);

	if (pCV != NULL)
	{
		ProcessAction(szId, pCV);
	}		
}

void JClientEvent::ProcessAction(const CString& szAction, G2JChartView *pCV)
{
	if (szAction == m_szCloseAction)
	{
		pCV->PostMessage(WM_DESTROY);
	}
	else if (szAction == m_szSizedAction)
	{
		int width = toInt(getText(m_pRoot, m_szWidthTag));
		int height = toInt(getText(m_pRoot, m_szHeightTag));
		pCV->SetWindowPos(NULL, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER | SWP_HIDEWINDOW);
	}
	else if (szAction == m_szClickedAction) {
		double* buf = new double[5];
		buf[0] = toDouble(getText(m_pRoot, m_szXTag));		//x
		buf[1] = toDouble(getText(m_pRoot, m_szYTag));		//y
		buf[2] = toDouble(getText(m_pRoot, m_szZTag));		//z
		buf[3] = toInt(getText(m_pRoot, m_szSubsetTag));//subset
		buf[4] = toInt(getText(m_pRoot, m_szPointTag)); //point

		pCV->PostMessage(WM_CLICK_ACTION, (WPARAM)buf);
	}
}

JClientMessage* JClientEvent::Clone(xmlNodePtr pRoot)
{
	return new JClientEvent(pRoot);
}

// -------+++++++------- JClientError class -------+++++++------- //
const CString JClientError::m_szIdentifier = _T("ChartError");
const CString JClientError::m_szTextTag = _T("text");

extern "C" long g2ext_write_string_to_console(char* message);
void JClientError::Process()
{
	USES_CONVERSION;

	CString message = getText(m_pRoot, m_szTextTag);
	
	g2ext_write_string_to_console(T2A(message));
}

JClientMessage* JClientError::Clone(xmlNodePtr pRoot)
{
	return new JClientError(pRoot);
}
