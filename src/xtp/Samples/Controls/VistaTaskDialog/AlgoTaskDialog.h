#pragma once


class CAlgoTaskDialog : public CXTPTaskDialog
{
public:
	CAlgoTaskDialog(void);
	virtual ~CAlgoTaskDialog(void);

protected:
	BOOL CopyToClipboard(const CString& strText);
	void UpdateFooterText();
	virtual void OnDialogConstructed();
	virtual void OnButtonClicked(int nButtonID, BOOL& bCloseDialog);

	CSize m_avgCharPix;
	CSize m_avgCharDlu;

	CString m_strHeaderText;
	CString m_strFooterText;
	CXTPEmptySize m_sizeClient;
	CXTPEmptySize m_sizeDlu;

};
