// HisTreeCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "HisTreeCtrl.h"
#include "HistoryTree.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////////////////////////////////////////////
// CHisTreeCtrl

CHisTreeCtrl::CHisTreeCtrl()
{
}

CHisTreeCtrl::~CHisTreeCtrl()
{
	m_astrHist.RemoveAll();
}


BEGIN_MESSAGE_MAP(CHisTreeCtrl, CTreeCtrl)
	//{{AFX_MSG_MAP(CHisTreeCtrl)
	ON_NOTIFY_REFLECT(NM_CLICK, OnClick)
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHisTreeCtrl message handlers


void CHisTreeCtrl::OnClick(NMHDR* /*pNMHDR*/, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	HTREEITEM hItem;
	
	CPoint pt;
	try{

	GetCursorPos(&pt);
	ScreenToClient(&pt);
	hItem = HitTest(pt);

	if ((hItem != NULL) && !ItemHasChildren(hItem))
	{
		int nImg, nOImg;
		GetItemImage(hItem, nImg, nOImg);
		if(nImg==2)
		{
			OpenWindow(m_astrHist[GetItemData(hItem)-1]);
		}
		else
		{
			//get folder
			LPITEMIDLIST pidlHistory = NULL;

		   HRESULT hr = SHGetSpecialFolderLocation(NULL, CSIDL_HISTORY, &pidlHistory);
		   if (NOERROR != hr)
			  return;

		   IShellFolder* psfDesktop;
		   IShellFolder* psfHistory;

		   hr = SHGetDesktopFolder(&psfDesktop);
		   if (NOERROR != hr)
			  return;

		   hr = psfDesktop->BindToObject(pidlHistory, NULL, IID_IShellFolder,
										 (LPVOID*)&psfHistory);
		   psfDesktop->Release();

		   if (NOERROR != hr)
			  return;

		   HTREEITEM hDayItem;
		   hDayItem = GetParentItem(hItem);
		   if(hDayItem == NULL)
			   hDayItem = hItem;

			CString folder = GetItemText(hDayItem);
			LPITEMIDLIST pidlSubFolder = FindFolder(folder, psfHistory);
			if(pidlSubFolder!=NULL)
			{
				IShellFolder* psfSubFolder = NULL;
				IShellFolder* psfSubFolder2 = NULL;
			    hr = psfHistory->BindToObject(pidlSubFolder, NULL, IID_IShellFolder,
					 (LPVOID*)&psfSubFolder);

				if( hDayItem != hItem)
				{
					if (pidlSubFolder)
						((CHistoryTree*)m_pHisTree)->m_pMalloc->Free(pidlSubFolder);

					folder = GetItemText(hItem);
					pidlSubFolder = FindFolder(folder, psfSubFolder);
					//psfSubFolder->Release();
					hr = psfSubFolder->BindToObject(pidlSubFolder, NULL, IID_IShellFolder,
						 (LPVOID*)&psfSubFolder2);
				}
				if(nImg ==0)
					((CHistoryTree*)m_pHisTree)->AddHistory(psfSubFolder, hItem, 1,3);
				else
					((CHistoryTree*)m_pHisTree)->AddHistory(psfSubFolder2, hItem, 2,2);

				if(psfSubFolder)
					psfSubFolder ->Release();
				if(psfSubFolder2)
					psfSubFolder2 ->Release();
			}

			((CHistoryTree*)m_pHisTree)->m_pMalloc->Free(pidlSubFolder);
		   ((CHistoryTree*)m_pHisTree)->m_pMalloc->Free(pidlHistory);

		   psfHistory->Release();

			Expand(hItem,TVE_TOGGLE);
		}
	}
	else
		Expand(hItem,TVE_TOGGLE);

	}catch(...)
	{
	}

	*pResult = 0;
	
}

LPITEMIDLIST CHisTreeCtrl::FindFolder(LPCTSTR foldername, IShellFolder *pFolder)
{
	IEnumIDList* pItems = NULL;
	LPITEMIDLIST pidlNext = NULL;
	CString lpszName;

	HRESULT hr = pFolder->EnumObjects(NULL, SHCONTF_FOLDERS|SHCONTF_NONFOLDERS, &pItems);
   while (NOERROR == hr)
   {
	  hr = pItems->Next(1, &pidlNext, NULL);
	  if (NOERROR == hr)
	  {
         m_pHisTree->GetName(pFolder, pidlNext, SHGDN_NORMAL, lpszName);

		 if(_tcscmp(foldername, lpszName)==0)
		 {
	 		 if (pItems)
				  pItems->Release();
			 return pidlNext;
		 }
		 else if (pidlNext)
		 {		 
			((CHistoryTree*)m_pHisTree)->m_pMalloc->Free(pidlNext);
		 }

	  }
   }

   if (pItems)
	  pItems->Release();

   return NULL;
}


void CHisTreeCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	CTreeCtrl::OnMouseMove(nFlags, point);
}

