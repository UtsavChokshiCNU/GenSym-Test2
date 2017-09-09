// MessageRecord.h: interface for the CMessageRecord class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MESSAGERECORD_H__AFFF918D_1624_41E5_8902_81B1F0C749BA__INCLUDED_)
#define AFX_MESSAGERECORD_H__AFFF918D_1624_41E5_8902_81B1F0C749BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CReportSampleView;

//////////////////////////////////////////////////////////////////////////
// Customized record item, used for displaying prices.
class CMessageRecordItemPrice : public CXTPReportRecordItemNumber
{
	DECLARE_SERIAL(CMessageRecordItemPrice)
public:
	// Constructs record item with the initial decimal price value.
	CMessageRecordItemPrice(double dValue = .0);

	// Provides custom group captions depending on the price.
	virtual CString GetGroupCaption(CXTPReportColumn* pColumn);

	// Provides custom group values comparison based on price value, 
	// instead of based on captions.
	virtual int CompareGroupCaption(CXTPReportColumn* pColumn, CXTPReportRecordItem* pItem);
};

//////////////////////////////////////////////////////////////////////////
// Customized record item, used for displaying checkboxes.
class CMessageRecordItemCheck : public CXTPReportRecordItem
{
	DECLARE_SERIAL(CMessageRecordItemCheck)
public:
	// Constructs record item with the initial checkbox value.
	CMessageRecordItemCheck(BOOL bCheck = FALSE);

	// Provides custom group captions depending on checkbox value.
	// Returns caption string ID to be read from application resources.
	virtual int GetGroupCaptionID(CXTPReportColumn* pColumn);

	// Provides custom records comparison by this item based on checkbox value, 
	// instead of based on captions.
	virtual int Compare(CXTPReportColumn* pColumn, CXTPReportRecordItem* pItem);
};

//////////////////////////////////////////////////////////////////////////
// Enumerates possible Message Importance values for using by 
// CMessageRecordItemImportance class
typedef enum MESSAGE_IMPORTANCE
{
	msgImportanceNormal,
	msgImportanceHigh,
	msgImportanceLow
};

//////////////////////////////////////////////////////////////////////////
// Customized record item, used for displaying importance icons.
class CMessageRecordItemImportance : public CXTPReportRecordItem
{
	DECLARE_SERIAL(CMessageRecordItemImportance)
public:
	// Constructs record item with the initial value.
	CMessageRecordItemImportance(MESSAGE_IMPORTANCE eImportance = msgImportanceNormal);
	
	virtual void DoPropExchange(CXTPPropExchange* pPX);
protected:
	MESSAGE_IMPORTANCE m_eImportance;   // Message importance
};

//////////////////////////////////////////////////////////////////////////
// Customized record item, used for displaying attachments icons.
class CMessageRecordItemAttachment : public CXTPReportRecordItem
{
	DECLARE_SERIAL(CMessageRecordItemAttachment)
public:
	// Constructs record item with the initial value.
	CMessageRecordItemAttachment(BOOL bHasAttachment = FALSE);

	virtual void DoPropExchange(CXTPPropExchange* pPX);
protected:
	BOOL m_bHasAttachment;	// TRUE when message has attachments, FALSE otherwise.
};

//////////////////////////////////////////////////////////////////////////
// Customized record item, used for displaying read/unread icons.
class CMessageRecordItemIcon : public CXTPReportRecordItem
{
	DECLARE_SERIAL(CMessageRecordItemIcon)
public:
	// Constructs record item with the initial read/unread value.
	CMessageRecordItemIcon(BOOL bRead = FALSE);

	// Provides custom group captions depending on the read/unread value.
	virtual CString GetGroupCaption(CXTPReportColumn* pColumn);

	// Provides custom group values comparison based on read/unread value, 
	// instead of based on captions.
	virtual int CompareGroupCaption(CXTPReportColumn* pColumn, CXTPReportRecordItem* pItem);

	// Updates record item icon index depending on read/unread value.
	void UpdateReadIcon();

	// Provides custom records comparison by this item based on read/unread value, 
	// instead of based on captions.
	int Compare(CXTPReportColumn* pColumn, CXTPReportRecordItem* pItem);

	virtual void DoPropExchange(CXTPPropExchange* pPX);
public:
	BOOL m_bRead;	// TRUE for read, FALSE for unread.
};

//////////////////////////////////////////////////////////////////////////
// Customized record Date/Time item.
// Main customization purpose is overriding GetGroupCaptionID and providing
// application-specific caption when Report control data is grouped via this item.
class CMessageRecordItemDate : public CXTPReportRecordItemDateTime
{
	DECLARE_SERIAL(CMessageRecordItemDate)
public:
	// Construct record item from COleDateTime value.
	CMessageRecordItemDate(COleDateTime odtValue = COleDateTime::GetCurrentTime());

	// Provides custom group captions depending on the item date value.
	virtual int GetGroupCaptionID(CXTPReportColumn* pColumn);
};

//////////////////////////////////////////////////////////////////////////
// This class is your main custom Record class which you'll manipulate with.
// It contains any kind of specific methods like different types of constructors,
// any additional custom data as class members, any data manipulation methods.
class CMessageRecord : public CXTPReportRecord
{
	DECLARE_SERIAL(CMessageRecord)
public:
	
	// Construct record object using empty values on each field
	CMessageRecord();
	
	// Construct record object from detailed values on each field
	CMessageRecord(
		MESSAGE_IMPORTANCE eImportance, BOOL bChecked, int  nAttachmentBitmap,
		CString strFromName, CString strSubject,
		COleDateTime odtSent, int nMessageSize, BOOL bRead,
		double dPrice, COleDateTime odtReceived, COleDateTime odtCreated,
		CString strConversation, CString strContact, CString strMessage,
		CString strCC, CString strCategories, CString strAutoforward,
		CString strDoNotAutoarch, CString strDueBy,
		CString strPreview
		);

	// Clean up internal objects
	virtual ~CMessageRecord();

	// Create record fields using empty values
	virtual void CreateItems();

	// Set message as read
	BOOL SetRead();

	// Overridden callback method, where we can customize any drawing item metrics.
	virtual void GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics);

	virtual void DoPropExchange(CXTPPropExchange* pPX);

	CMessageRecordItemIcon* m_pItemIcon;	// Display read/unread icon.
	CMessageRecordItemDate* m_pItemReceived;// Contains message receive time.
	CXTPReportRecordItem*	m_pItemSize;	// Message size. 
											// We are storing pointer to this item for further use.

};

#endif // !defined(AFX_MESSAGERECORD_H__AFFF918D_1624_41E5_8902_81B1F0C749BA__INCLUDED_)
