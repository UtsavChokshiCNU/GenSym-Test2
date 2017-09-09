#if !defined(AFX_RGTREECTRL_H__6DE6C0C5_8498_11D4_843E_02608CA1FA7B__INCLUDED_)
#define AFX_RGTREECTRL_H__6DE6C0C5_8498_11D4_843E_02608CA1FA7B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/**********************************************************************************************
 *                                                                                            *
 *  FILE: RGTreeCtrl.h                                                                        *
 *                                                                                            *
 *  DESCRIPTION:                                                                              *
 *       Declaration of the TreeCtrl class using the template CRGTreeT                        *
 *                                                                                            *
 *  René Greiner                                                                              *
 *    eMail: rene.greiner@gmx.de                                                            *
 *                                                                                            *
 **********************************************************************************************/

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the RGTREECTRL_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// RGTREECTRL_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.

#pragma once

#ifdef USE_DLL

#ifdef RGTREECTRL_EXPORTS
#define RGTREECTRL_API __declspec(dllexport)
#else
#define RGTREECTRL_API __declspec(dllimport)
#endif

#else

#define RGTREECTRL_API

#endif

extern "C" RGTREECTRL_API HWND CreateRGTree( DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HANDLE hInstance, LPVOID lpParam);

//extern "C" RGTREECTRL_API LRESULT CALLBACK RGTreeWindowProc( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

#ifdef __AFX_H__ // MFC project

/////////////////////////////////////////////////////////////////////////////
// CRGTreeCtrl window ( MFC )
#define RG_TREE_WITH_WND_PROC_MAP
#define WM_TREECTRL_CHECKANDLOADNODES	WM_USER + 200
class RGTREECTRL_API CRGTreeCtrl : public CTreeCtrl
{
protected:
  virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
  virtual void PreSubclassWindow();
  
  bool m_bCreated;
  
public:
    CRGTreeCtrl();
  
  virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
  
  // advanced creation (allows access to extended styles)
  /*BOOL CreateEx(DWORD dwExStyle, LPCTSTR lpszClassName,
    LPCTSTR lpszWindowName, DWORD dwStyle,
    int x, int y, int nWidth, int nHeight,
    HWND hWndParent, HMENU nIDorHMenu, LPVOID lpParam = NULL);
  
  BOOL CreateEx(DWORD dwExStyle, LPCTSTR lpszClassName,
    LPCTSTR lpszWindowName, DWORD dwStyle,
    const RECT& rect,
    CWnd* pParentWnd, UINT nID,
    LPVOID lpParam = NULL);*/

  static BOOL staticOnWndMsg(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
  {
    return ((CRGTreeCtrl*)CWnd::FromHandle(hwnd))->OnWndMsg(message, wParam, lParam, pResult);
  }

  DECLARE_DYNCREATE(CRGTreeCtrl);
};

#endif //__AFX_H__

#endif // !defined(AFX_RGTREECTRL_H__6DE6C0C5_8498_11D4_843E_02608CA1FA7B__INCLUDED_)
