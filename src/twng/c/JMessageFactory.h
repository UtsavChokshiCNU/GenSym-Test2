#include <libxml\parser.h>

class JClientMessage;
class JString;
class G2JChartView;

class JMessageFactory
{
public:
	static JMessageFactory* GetInstance();

	bool ProcessMessage(const CString& szMessage);
	
protected:	

	JClientMessage* Get(LPCSTR szAction, xmlNodePtr pRoot);

	JMessageFactory();

	typedef struct TPair
	{
		TPair(CString szKey=_T(""), JClientMessage* pMessage = NULL): m_szKey(szKey), m_pMessage(pMessage) {}
		CString m_szKey;
		JClientMessage* m_pMessage;
	} Pair;

	typedef CArray<Pair, Pair> CContainer;
	CContainer m_Container;

	static const CString m_szActionTag;
};

class JClientMessage
{
public:
	JClientMessage() : m_pRoot(NULL) {}
	virtual ~JClientMessage() {}

	virtual void Process() = 0;

	virtual JClientMessage* Clone(xmlNodePtr pRoot) = 0;

protected:
	JClientMessage(xmlNodePtr pRoot): m_pRoot(pRoot) {}

	xmlNodePtr m_pRoot;
	
	static const CString m_szHandleTag;
};

class JClientEvent: public JClientMessage
{
public:
	JClientEvent() {}
	virtual ~JClientEvent() {}
	virtual void Process();
	virtual JClientMessage* Clone(xmlNodePtr pRoot);

public:
	static const CString m_szIdentifier;

protected:
	JClientEvent(xmlNodePtr pRoot): JClientMessage(pRoot) {}

	void ProcessAction(const CString& szAction, G2JChartView *pCV);

protected:
	static const CString m_szIdTag;
	static const CString m_szWidthTag;
	static const CString m_szHeightTag;

	static const CString m_szCloseAction;
	static const CString m_szSizedAction;

	static const CString m_szClickedAction;
	static const CString m_szXTag;
	static const CString m_szYTag;
	static const CString m_szZTag;
	static const CString m_szSubsetTag;
	static const CString m_szPointTag;
};

class JClientError: public JClientMessage
{
public:
	JClientError() {}
	virtual ~JClientError() {}
	virtual void Process();
	virtual JClientMessage* Clone(xmlNodePtr pRoot);

public:
	static const CString m_szIdentifier;
	static const CString m_szTextTag;

protected:
	JClientError(xmlNodePtr pRoot): JClientMessage(pRoot) {}

};
