#pragma once

class CProgressEffectsDialog : public CXTPTaskDialog
{
public:
	CProgressEffectsDialog(CWnd* pWndParent);

protected:
	virtual void OnDialogConstructed();
	virtual void OnButtonClicked(int nButtonID, BOOL& bCloseDialog);

private:
	void UpdateMainInstruction();
	void CycleState();
	void ToggleMode();

	int  m_eState;
	BOOL m_bMarquee;

	CString m_strContext;

};

class CDynamicTextDialog : public CXTPTaskDialog
{
public:
	CDynamicTextDialog(CWnd* pWndParent);

protected:
	virtual void OnDialogConstructed();
	virtual void OnButtonClicked(int nButtonID, BOOL& bCloseDialog);

private:
};


class CTimerDialog : public CXTPTaskDialog
{
public:
	CTimerDialog(CWnd* pWndParent);

protected:
	virtual void OnDialogConstructed();
	virtual void OnTimer(DWORD dwMilliSeconds, BOOL& bReset);
	virtual void OnVerificationClicked(BOOL bChecked);
	virtual void OnButtonClicked(int nButtonID, BOOL& bCloseDialog);

	int m_nIcon;
	BOOL m_bUpdateIcon;
};


#define ID_BUTTON_NEXT 101
#define ID_BUTTON_PREV 100

class CPropetySheetTaskDialog
{
public:
	
	
	class CTaskDialogPage : public CXTPTaskDialog
	{
	public:
		CTaskDialogPage(CWnd* pWndParent = NULL)
			: CXTPTaskDialog(pWndParent)
		{
			SetCommonButtons(TDCBF_CANCEL_BUTTON);
			SetWindowTitle(_T("PropertySheet Sample"));
			SetMainInstruction(_T("Follow steps to finish wizard"));
			
			m_pPagePrev = 0;
			m_pPageNext = 0;
		}
		
		virtual void OnDialogConstructed()
		{
			EnableButton(ID_BUTTON_PREV, m_pPagePrev != NULL);
		}
		virtual void OnNavigated()
		{
			OnDialogConstructed();
			
		};
		
		void OnButtonClicked(int nButtonID, BOOL& bCloseDialog)
		{
			switch (nButtonID)
			{
			case ID_BUTTON_PREV: if (m_pPagePrev) NavigatePage(*m_pPagePrev); bCloseDialog = FALSE; break;
			case ID_BUTTON_NEXT: if (m_pPageNext) NavigatePage(*m_pPageNext);  bCloseDialog = FALSE; break;
			}
		}
	public:
		CTaskDialogPage* m_pPagePrev;
		CTaskDialogPage* m_pPageNext;
	};
	
	
	class CPage1 : public CTaskDialogPage
	{
	public:
		CPage1(CWnd* pWndParent)
			: CTaskDialogPage(pWndParent)
		{
			AddButton(_T("&Prev"), ID_BUTTON_PREV);
			AddButton(_T("&Next"), ID_BUTTON_NEXT);
			SetContent(_T("Page 1"));
			SetExpandedInformation(_T("Prepare to see 4 pages :)"));
		}	
	};
	
	class CPage2 : public CTaskDialogPage
	{
	public:
		CPage2()
		{
			AddButton(_T("&Prev"), ID_BUTTON_PREV);
			AddButton(_T("&Next"), ID_BUTTON_NEXT);

			AddRadioButton(_T("First Option"), 200);
			AddRadioButton(_T("Next Option"), 201);
			SetDefaultRadioButton(m_nOption = 200);

			SetContent(_T("Page 2"));
			SetDefaultButton(ID_BUTTON_NEXT);
		}
		void OnRadioButtonClicked(int nButtonID) 
		{
			SetDefaultRadioButton(m_nOption = nButtonID);
		}

	public:
		int m_nOption;
	};
	class CPage3 : public CTaskDialogPage
	{
	public:
		CPage3()
		{
			AddButton(_T("&Prev"), ID_BUTTON_PREV);
			AddButton(_T("&Next"), ID_BUTTON_NEXT);
			SetContent(_T("Page 3"));	
			SetDefaultButton(ID_BUTTON_NEXT);

			SetVerificationText(_T("Enable this option"));
			SetVerifyCheckState(m_bState = TRUE);
		}
		void OnVerificationClicked(BOOL bChecked) 
		{
			SetVerifyCheckState(m_bState = bChecked);
		}
	public:
		BOOL m_bState;

	};
	
	class CPage4 : public CTaskDialogPage
	{
	public:
		CPage4()
		{
			AddButton(_T("&Prev"), ID_BUTTON_PREV);
			AddButton(_T("&Finish"), IDOK);
			SetContent(_T("Page 4"));	
			SetDefaultButton(IDOK);
		}	
	};
	
	CPropetySheetTaskDialog(CWnd* pWndParent)
		: m_page1(pWndParent)
	{
		m_page1.m_pPageNext = &m_page2;
		m_page2.m_pPagePrev = &m_page1;
		m_page2.m_pPageNext = &m_page3;
		m_page3.m_pPagePrev = &m_page2;
		m_page3.m_pPageNext = &m_page4;
		m_page4.m_pPagePrev = &m_page3;
		
	}
	
	INT_PTR DoModal(BOOL bUseComCtl32)
	{
		return m_page1.DoModal(bUseComCtl32);
	}

public:
	CPage1 m_page1;
	CPage2 m_page2;
	CPage3 m_page3;
	CPage4 m_page4;
};

