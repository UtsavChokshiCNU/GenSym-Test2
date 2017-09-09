// ModalEdit.cpp: implementation of the CModalEdit class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "Twng.h"
#include "MainFrm.h"
#include "filedlg.h"		// Resizer
#include "ddrsc.h"		// Resource IDs
#include "ScintillaWnd.h"
#include "Editor.h"
#include "ModalEdit.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNCREATE(CModalEdit,CDialog)

BEGIN_MESSAGE_MAP(CModalEdit,CDialog)
  ON_WM_CLOSE()
  ON_WM_SIZE()
END_MESSAGE_MAP()

CModalEdit::CModalEdit(int handle) : CDialog(IDD_MODALEDITOR)
{

}
CModalEdit::~CModalEdit()
{
	if (m_EditorWnd != NULL) {
		delete m_EditorWnd;
		m_EditorWnd = NULL;
	}

	if (m_pParent != NULL) {
		delete m_pParent;
		m_pParent = NULL;
	}
}

void CModalEdit::DoDataExchange(CDataExchange* pDX) // virtual
{
  CDialog::DoDataExchange(pDX);
}

BOOL CModalEdit::OnInitDialog()
{
  CDialog::OnInitDialog();
   
  m_pParent->SetParent(this);
  
 // CRect cRect;
 // m_pParent->GetClientRect(&cRect);
 // this->MoveWindow(&cRect);

  return TRUE;
}
void CModalEdit::Create(long Handle){
	m_iHandle = Handle;
	CDialog::Create(IDD_MODALEDITOR,NULL);
};

void CModalEdit::OnClose() 
{
	::SendMessage(m_pParent->GetSafeHwnd(), WM_CLOSE, 0,0);
	CDialog::OnClose();
}
void CModalEdit::OnSize(UINT nType, int cx, int cy) 
{
  CDialog::OnSize(nType, cx, cy);
    
  CRect cRect;
  this->GetClientRect(&cRect);
  m_pParent->MoveWindow(&cRect);
  m_pParent->ShowWindow(SW_SHOW);
}
