// PropertyDlg.h: header file
//
#pragma once

#include "resource.h"

class CPropertyDlg : public CDialog
{
public:
   CPropertyDlg(CWnd* pParent=NULL);
   virtual ~CPropertyDlg() {};

   enum {IDD = IDD_PROPDLG};

protected:
   virtual void DoDataExchange(CDataExchange* pDX);
   DECLARE_MESSAGE_MAP()

public :
   CString m_id;
   CString m_description;
};
