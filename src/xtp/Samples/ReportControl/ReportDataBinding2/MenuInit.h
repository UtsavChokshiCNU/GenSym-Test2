////////////////////////////////////////////////////////////////
// Microsoft Systems Journal -- November 1999
// If this code works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
// Compiles with Visual C++ 6.0, runs on Windows 98 and probably NT too.
//
#pragma once

//////////////////
// Initialize any menu by routing through any MFC command target.
//
class CPopupMenuInit {
public:
	static void Init(CCmdTarget* pTarg,
		CMenu* pMenu, BOOL bAutoMenuEnable=TRUE);
};
