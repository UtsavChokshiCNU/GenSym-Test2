/////////////////////////////////////////////////////////////////////////////
//
// ConfirmExitDlg.h : header file
//
/////////////////////////////////////////////////////////////////////////////
#pragma once
#include "Resource.h"

// Registry section to hold values
extern LPCTSTR ConfirmExitDialog_RegSection;

// Registry entry to hold state of "Don't ask again" checkbox
extern LPCTSTR ConfirmExitDialog_DontAskAgain_RegEntry;

// Ask (if necessary) user to exit
bool ConfirmExitDialog_AskToExit();

// Return dialog window handle
const HWND& GetConfirmExitDialogHandle();
