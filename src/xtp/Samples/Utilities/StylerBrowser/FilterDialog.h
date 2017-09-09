#pragma once

// CFilterDialog dialog

class CFilterDialog : public CDialog
{
	DECLARE_DYNAMIC(CFilterDialog)

public:
	CFilterDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CFilterDialog();

	CXTPEditListBox m_LBEditor;

// Dialog Data
	enum { IDD = IDD_DIALOG_FILTER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:

	

	static void LoadFilterList();

	static CStringArray m_lstFilter;
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
public:
	void SaveFilterList(void);
};
