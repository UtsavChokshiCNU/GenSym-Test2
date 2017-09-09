// Based on example from September 2000 MSDN Magazine
// in C++ Q&A Tooltip article by Paul DiLascia (p155)
//
// Parent message filter based on CodeProject article 
// "An Enhanced CCheckComboBox" by Magerusan Grigore Cosmin 


#pragma once

#include "subclass.h"

class ComboTree;

//////////////////
// Intercepts parent window messages
// To use:
// - used within ComboTree
// - call Init, passing parent window of ComboTree
//
class ComboTreeHook : public CSubclassWnd {
protected:

	// subclass window proc
	virtual LRESULT WindowProc(UINT msg, WPARAM wp, LPARAM lp);


public:
	ComboTreeHook();
	~ComboTreeHook();
	void Init(HWND hParent, ComboTree* pTreeCombo, BOOL bHookNow = FALSE); // initialize

	void HookParent();    //Must call this when tree is dropped down
	void UnhookParent();  //Must call this when tree is hidden


protected:
	BOOL IsMsgOK(UINT nMsg, WPARAM wParam, LPARAM lParam);

private:
	ComboTree* m_pComboTree;
	HWND m_hParent;
};
