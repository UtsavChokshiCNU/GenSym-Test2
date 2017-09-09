// DynamicDlg.h : header file
//
#include "DynamicBaseDlg.h"


struct CTVData // allocated memory for combo tree hjg 01-14-2005
{
  CComboBox *p_ComboToSubclass;
  ComboTree *p_ComboTree;
};


class CDynamicDlg : public CDynamicBaseDlg
{
public:
  DECLARE_DYNCREATE(CDynamicDlg)
  CDynamicDlg(int handle = 0);
  virtual ~CDynamicDlg();

private:
  int m_handle;			// G2-assigned Native window handle

  // Overrides
public:
  virtual BOOL PreTranslateMessage(MSG* pMsg);

protected:
  virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

protected:
  DECLARE_MESSAGE_MAP()
};
