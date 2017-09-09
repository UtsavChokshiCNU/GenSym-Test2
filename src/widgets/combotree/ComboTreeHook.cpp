////////////////////////////////////////////////////////////////
// Based on example from September 2000 MSDN Magazine
// in C++ Q&A Tooltip article by Paul DiLascia (p155)
//
// Parent message filter based on CodeProject article 
// "An Enhanced CCheckComboBox" by Magerusan Grigore Cosmin 
// http://www.codeproject.com/combobox/checkcmb.asp

#include "stdafx.h"
#include "ComboTreeHook.h"
#include "ComboTree.h"

ComboTreeHook::ComboTreeHook()
{
	m_pComboTree = NULL;
	m_hParent = NULL;
}

ComboTreeHook::~ComboTreeHook()
{
}

//////////////////
// Initialize hooked parent and tree
// Install hook (optional)
//
void ComboTreeHook::Init(HWND hParent, ComboTree* pComboTree, BOOL bHookNow)
{
	m_pComboTree = pComboTree;
	m_hParent = hParent;
	if (bHookNow)
	{
		CSubclassWnd::HookWindow(hParent);
	}
}

//////////////////
// "Hook" function traps messages sent to parent
//
LRESULT ComboTreeHook::WindowProc(UINT msg, WPARAM wp, LPARAM lp)
{
	BOOL bHideDropDown = FALSE;
	switch (msg)
	{
	case WM_COMMAND:
		bHideDropDown = bHideDropDown = !IsMsgOK( msg, wp, lp);	
		break;
	case WM_SYSCOMMAND:
	case WM_SYSKEYDOWN:
	case WM_LBUTTONDOWN:
	case WM_NCLBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_NCRBUTTONDOWN:
	case WM_MBUTTONDOWN:
	case WM_NCMBUTTONDOWN:
	case WM_WINDOWPOSCHANGING:
	case WM_WINDOWPOSCHANGED:
		bHideDropDown = TRUE;	
		break;
		
	default:
		break;
	};
	
	
	LRESULT ret = CSubclassWnd::WindowProc(msg, wp, lp);
	if (bHideDropDown)
	{
//		TRACE("ParentWindowProc() Hiding Active Dropdown\n");
		if (m_pComboTree)
		{
			m_pComboTree->SendParentComboMessage (CBN_KILLFOCUS);
			m_pComboTree->OnCancel ();
		}
	}
	return ret;

}

//////////////////
// Filter parent window messages. Hide tree if not a notification message from tree 
//
BOOL ComboTreeHook::IsMsgOK(UINT nMsg, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(wParam);

	BOOL bRet = FALSE;

	if (nMsg != WM_COMMAND)
	{
		return bRet;
	}

	if (!m_pComboTree)
	{
		return bRet;
	}


	if (lParam == NULL)
	{
		//message not from a control
		return bRet;
	}


	UINT nID = m_pComboTree->GetDlgCtrlID();
	if (LOWORD(wParam) == nID)
	{
		return TRUE;
	}


	return bRet;
}


//Must call this when tree is dropped down
void ComboTreeHook::HookParent()
{
	ASSERT( m_pComboTree && m_hParent);

	if (m_pComboTree && m_hParent)
	{
		CSubclassWnd::HookWindow(m_hParent);
	}
}

//Must call this when tree is hidden
void ComboTreeHook::UnhookParent()   
{
	ASSERT( m_pComboTree && m_hParent);

	if (m_pComboTree && m_hParent)
	{
		CSubclassWnd::Unhook();
	}

}
