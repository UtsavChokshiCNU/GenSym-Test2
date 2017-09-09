// ModalEdit.h: interface for the CModalEdit class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MODALEDIT_H__3C01C216_E05F_417F_9FC1_DD289823815B__INCLUDED_)
#define AFX_MODALEDIT_H__3C01C216_E05F_417F_9FC1_DD289823815B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "EditorFrame.h"
class CModalEdit : public CDialog
{
   DECLARE_DYNCREATE(CModalEdit)
public:
  CModalEdit(int handle = 0);
  virtual ~CModalEdit();
  G2Editor *m_EditorWnd;
  CFrameWnd *m_pParent;
  int m_iHandle;
protected:
  DECLARE_MESSAGE_MAP()
public:				// Automatically generated declarations
  void Create(long Handle);
  virtual void DoDataExchange(CDataExchange* pDX);
  afx_msg void OnClose();
  afx_msg BOOL OnInitDialog();
  afx_msg void OnSize(UINT nType, int cx, int cy);
};

#endif // !defined(AFX_MODALEDIT_H__3C01C216_E05F_417F_9FC1_DD289823815B__INCLUDED_)
